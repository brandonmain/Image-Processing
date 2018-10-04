/**
 * Basic library for reading and writing images.
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/**
 * @brief      Given an Matrix, will display the matrix.
 *
 * @param      A matrix that should constitute an image.
 */
void displayIMG(const char* WINDOW, Mat &image)
{
    namedWindow( WINDOW, WINDOW_AUTOSIZE );// Create a WINDOW for display.
    imshow( WINDOW, image );    // Show our image inside it.

    waitKey(0);      // Wait for a keystroke in the WINDOW
}

/**
 * @brief      Writes an image to a file in binary (0) format
 *             for pgm images.
 *
 * @param[in]  FILE   The file
 * @param      image  The image
 */
void writeIMG(const char* FILE, Mat &image)
{
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PXM_BINARY);
    compression_params.push_back(0);

    imwrite(FILE, image, compression_params);
}