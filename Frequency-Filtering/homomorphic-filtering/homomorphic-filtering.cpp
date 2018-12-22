/**
 * Homomorphic Filtering
 */

#include <iostream>
#include <cmath>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void fftshift(const Mat& inputImg, Mat& outputImg);
void filter2DFreq(const Mat& inputImg, Mat& outputImg, const Mat& H);
void highpassFilter(Mat& H);

int main(int argc, char** argv)
{
	Mat imgIn = imread(argv[1], IMREAD_GRAYSCALE);
    if (imgIn.empty()) //check whether the image is loaded or not
    {
        cout << "ERROR : Image cannot be loaded..!!" << endl;
        return -1;
    }
    imgIn.convertTo(imgIn, CV_32F);

    // it needs to process even image only
    Rect roi = Rect(0, 0, imgIn.cols & -2, imgIn.rows & -2);
    imgIn = imgIn(roi);

    //Apply natural log to image
    for (int i = 0; i < imgIn.rows; ++i)
    {
        for (int j = 0; j < imgIn.cols; ++j)
        {
            imgIn.at<float>(i,j) = log(imgIn.at<float>(i,j));
        }
    }
    
    //Make highpass filter
    Mat H = Mat(roi.size(), CV_32F, Scalar(1));
    highpassFilter(H);
    
    Mat imgOut;
    fftshift(H, H);
    filter2DFreq(imgIn, imgOut, H);

    //Take exponential of image now
    for (int i = 0; i < imgOut.rows; ++i)
    {
        for (int j = 0; j < imgOut.cols; ++j)
        {
            imgOut.at<float>(i,j) = exp(imgOut.at<float>(i,j));
        }
    }
    
    // filtering (stop)
    imgOut.convertTo(imgOut, CV_8U);
    normalize(imgOut, imgOut, 0, 255, NORM_MINMAX);
    imwrite("result.png", imgOut);
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
    magnitude(planes[0], planes[1], outputImg);
}

void highpassFilter(Mat& H)
{
    float c = .5;
    float high = 1.5;
    float low = .5;

    for (int i = 0; i < H.rows; ++i)
    {
        for (int j = 0; j < H.cols; ++j)
        {
            H.at<float>(i,j) = (high - low)*(1.0 - exp(-1.0 * c * ((((float)i - H.rows/2.0) * ((float)i - H.rows/2.0) + ((float)j - H.cols/2.0) * ((float)j - H.cols/2.0)) / (1.8 * 1.8)))) + low;
        }
    }
}














