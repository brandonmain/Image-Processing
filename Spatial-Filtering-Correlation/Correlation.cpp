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

int main(int argc, char** argv)
{  
    //Read images in from command line.
    Mat pattern_image = imread(argv[1], IMREAD_GRAYSCALE);
    Mat image = imread(argv[2], IMREAD_GRAYSCALE);

    //Write image back to file just in case it's not
    //in the proper format for processing.
    writeIMG(argv[1], pattern_image);
    writeIMG(argv[2], image);

    //Correlation mask.
    Mat mask(pattern_image.rows, pattern_image.cols, CV_8U);

    /**
     * Need to write this function
     */
    setMaskWeights(mask, pattern_image);


    return 0;
}

         
/**
 * @brief      Sets the weights of a mask determined by the image
 *             that is input with it.
 *
 * @param      mask   The mask
 * @param      image  The image
 */
void setMaskWeights(Mat &mask, Mat &image)
{
    
}
