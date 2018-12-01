/**
 * Periodic noise removal.
 */

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void fftshift(const Mat& inputImg, Mat& outputImg);
void filter2DFreq(const Mat& inputImg, Mat& outputImg, const Mat& H);
void FilterH(Mat& inputOutput_H, Point center, int radius);
void calcPSD(const Mat& inputImg, Mat& outputImg, int flag = 0);

int main(int argc, char** argv)
{
    //Read in the image
    Mat imgIn = imread(argv[1], IMREAD_GRAYSCALE);
    if (imgIn.empty()) //check whether the image is loaded or not
    {
        cout << "ERROR : Image cannot be loaded..!!" << endl;
        return -1;
    }
    imgIn.convertTo(imgIn, CV_32F);

    //Make image width and height even
    Rect roi = Rect(0, 0, imgIn.cols & -2, imgIn.rows & -2);
    imgIn = imgIn(roi);

    //Power spectrum density calculation
    Mat imgPSD;
    calcPSD(imgIn, imgPSD);
    fftshift(imgPSD, imgPSD);
    normalize(imgPSD, imgPSD, 0, 255, NORM_MINMAX);

    //Make the filter
    Mat H = Mat(roi.size(), CV_32F, Scalar(1));

    //Radius chosen by inspection of image spectrum.
    //Points chosen upon inspection as well.
    //
    //This could also be done by implementing a function to 
    //check for large edge differences to find the spectrum peaks.
    //
    const int radius = 2;
    FilterH(H, Point(224, 240), radius);
    FilterH(H, Point(288, 240), radius);

    //Apply the filter to the image.
    Mat imgOut;
    fftshift(H, H);
    filter2DFreq(imgIn, imgOut, H);

    //Normalize resulting image and save.
    imgOut.convertTo(imgOut, CV_8U);
    normalize(imgOut, imgOut, 0, 255, NORM_MINMAX);
    imwrite("result.png", imgOut);
    imwrite("PSD.png", imgPSD);
    fftshift(H, H);
    normalize(H, H, 0, 255, NORM_MINMAX);
    imwrite("filter.png", H);
    return 0;
}

void fftshift(const Mat& inputImg, Mat& outputImg)
{
    outputImg = inputImg.clone();
    int cx = outputImg.cols / 2;
    int cy = outputImg.rows / 2;
    Mat q0(outputImg, Rect(0, 0, cx, cy));
    Mat q1(outputImg, Rect(cx, 0, cx, cy));
    Mat q2(outputImg, Rect(0, cy, cx, cy));
    Mat q3(outputImg, Rect(cx, cy, cx, cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}
void filter2DFreq(const Mat& inputImg, Mat& outputImg, const Mat& H)
{
    Mat planes[2] = { Mat_<float>(inputImg.clone()), Mat::zeros(inputImg.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI, DFT_SCALE);
    Mat planesH[2] = { Mat_<float>(H.clone()), Mat::zeros(H.size(), CV_32F) };
    Mat complexH;
    merge(planesH, 2, complexH);
    Mat complexIH;
    mulSpectrums(complexI, complexH, complexIH, 0);
    idft(complexIH, complexIH);
    split(complexIH, planes);
    outputImg = planes[0];
}
void FilterH(Mat& inputOutput_H, Point center, int radius)
{
    Point c2 = center, c3 = center, c4 = center;
    c2.y = inputOutput_H.rows - center.y;
    c3.x = inputOutput_H.cols - center.x;
    c4 = Point(c3.x,c2.y);

    //Create circles around points of interest.
    circle(inputOutput_H, center, radius, 0, -1, 8);
    circle(inputOutput_H, c2, radius, 0, -1, 8);
    circle(inputOutput_H, c3, radius, 0, -1, 8);
    circle(inputOutput_H, c4, radius, 0, -1, 8);
}

/**
 * @brief      Calculates the power spectrum density.
 *
 * @param[in]  inputImg   The input image
 * @param      outputImg  The output image
 * @param[in]  flag       The flag (0 or 1)
 */
void calcPSD(const Mat& inputImg, Mat& outputImg, int flag)
{
    Mat planes[2] = { Mat_<float>(inputImg.clone()), Mat::zeros(inputImg.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI);
    split(complexI, planes);            // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))
    planes[0].at<float>(0) = 0;
    planes[1].at<float>(0) = 0;
    // compute the PSD = sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)^2
    Mat imgPSD;
    magnitude(planes[0], planes[1], imgPSD);        //imgPSD = sqrt(Power spectrum density)
    pow(imgPSD, 2, imgPSD);                         //it needs ^2 in order to get PSD
    outputImg = imgPSD;
    // logPSD = log(1 + PSD)
    if (flag)
    {
        Mat imglogPSD;
        imglogPSD = imgPSD + Scalar::all(1);
        log(imglogPSD, imglogPSD);
        outputImg = imglogPSD;
    }
}
