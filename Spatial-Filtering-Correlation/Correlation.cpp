/**
 * Spatial Filtering (Correlation)
 * 
 * 
 *  by: Brandon Main
 *  
 *  compile with: g++ $(pkg-config --cflags --libs opencv) Correlation.cpp -o Correlation 
 */

#include "imageLib.h"

int main(int argc, char** argv)
{

    //Read image in from command line.
    Mat original_image = imread(argv[1], IMREAD_GRAYSCALE);

    //Write image back to file just in case it's not
    //in the proper format for processing.
    writeIMG(argv[1], original_image);


    /////////////////////////////////////////////////////
    // Need to write a function to perform correlation //
    /////////////////////////////////////////////////////


    return 0;
}
