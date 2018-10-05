/**
 * Spatial Filtering (Correlation)
 * 
 * @brief This program will attempt to find an image inside another
 *        image using correlation. The images should be given as
 *        command line arguements.
 *        
 * Usage:  ~$ ./Correlation image_to_find.pgm image_to_look_inside.pgm
 *  
 */


#include "imageLib.h"

void setMaskWeights(Mat &mask, Mat &image);
Mat addPadding(Mat &mask, Mat &image);
void correlate(Mat &mask, Mat &image);

int main(int argc, char** argv)
{  
    //Read images in from command line.
    Mat mask = imread(argv[1], IMREAD_GRAYSCALE);
    Mat image = imread(argv[2], IMREAD_GRAYSCALE);

    //Write image back to file just in case it's not
    //in the proper format for processing.
    writeIMG(argv[1], mask);
    writeIMG(argv[2], image);


    //Initialize padded image
    Mat padded_image(addPadding(mask, image));

    correlate(mask, padded_image);

    displayIMG("original", image);



    return 0;
}



/**
 * @brief      Adds padding to image based on mask size.
 *
 * @param      mask   The mask
 * @param      image  The image
 */
Mat addPadding(Mat &mask, Mat &image)
{
    int pad_rows = 2*(mask.rows -1);
    int pad_cols = 2*(mask.cols -1);

    Mat padded_image((image.rows + pad_rows), (image.cols + pad_cols), CV_8U);

    //Write 0s to image for padding
    for (int i = 0; i < padded_image.rows; ++i)
    {
        for (int j = 0; j < padded_image.cols; ++j)
        {
            padded_image.at<unsigned char>(i,j) = 0;
        }
    }

    //Write original image back in so it has padding 0s
    for (int i = pad_rows/2; i < (image.rows + pad_rows/2); ++i)
    {
        for (int j = pad_cols/2; j < (image.cols + pad_cols/2); ++j)
        {
            padded_image.at<unsigned char>(i,j) = image.at<unsigned char>(i - pad_rows/2,j - pad_cols/2);
        }
    }

    return padded_image;

}


/**
 * @brief      Applies sum of prducts to each pixel of an image.
 *
 * @param      mask          The mask
 * @param      padded_image  The padded image
 */
void correlate(Mat &mask, Mat &padded_image)
{
    int sum = 0;

    Mat summed_image(padded_image.rows, padded_image.cols, CV_8U);

    for (int i = 0; i < summed_image.rows; ++i)
    {
        for (int j = 0; j < summed_image.cols; ++j)
        {
            summed_image.at<unsigned char>(i,j) = 0;
        }
    }


    //Loop over entire image
    for (int pad_rows = 0; pad_rows < padded_image.rows; ++pad_rows)
    {
        for (int pad_cols = 0; pad_cols < padded_image.cols; ++pad_cols)
        {
            //Loop over mask
            for (int i = 0; i < mask.rows; ++i)
            {
                for (int j = 0; j < mask.cols; ++j)
                {
                    sum += mask.at<unsigned char>(i,j) * padded_image.at<unsigned char>(pad_rows, pad_cols);
                }
            }
            summed_image.at<unsigned char>(pad_rows,pad_cols) = sum;
            sum = 0;
        }
    }

    writeIMG("test.pgm", summed_image);

     for (int i = 0; i < summed_image.rows; ++i)
            {
                for (int j = 0; j < summed_image.cols; ++j)
                {
                    cout << summed_image.at<unsigned char>(i,j) << " ";
                }
            }

    displayIMG("img", summed_image);

    
}
