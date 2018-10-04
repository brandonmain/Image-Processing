/**
 * Basic library for displaying and writing images to file,
 * utilizes opencv. Also includes necessary opencv libraries.
 * 
 * Usage:
 *      Include this header file in desired program.
 *      
 *      ex: #include "imageLib.h"
 *      
 * Compile:
 *      Compile your main program with:
 *      
 *          g++ $(pkg-config --cflags --libs opencv) YOUR_PROGRAM.cpp -o YOUR_PROGRAM 
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
    // Create a window for display.
    namedWindow( WINDOW, WINDOW_AUTOSIZE );

    // Show our image inside it.
    imshow( WINDOW, image ); 

    // Wait for a keystroke in the WINDOW
    waitKey(0);
}

/**
 * @brief      Writes an image to a file in binary (0) format
 *             for pgm images. 
 *             
 * @reason     Sometimes images are in a Hex format when opened
 *             in a text editor. This function can be used to
 *             rewrite them back in an ASCII format.
 * 
 *
 * @param[in]  FILE   The file
 * @param      image  The image
 */
void writeIMG(const char* FILE, Mat &image)
{
    //Parameters to give to imwrite function for file writing.
    vector<int> params;
    params.push_back(CV_IMWRITE_PXM_BINARY);
    params.push_back(0);

    //Write to given file.
    imwrite(FILE, image, params);
}
