/*
 *  DFT.cpp
 *
 */


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


int main (int argc, char** argv)
{
    //Initiliaze matrix.
    //
    Mat f = (Mat_<float>(1,4) << 2, 3, 4, 4);

    cout << endl << "f is: "<< f << endl;

    //Get DFT of matrix.
    //
    Mat dft_f;
    dft(f, dft_f, DFT_COMPLEX_OUTPUT);

     //Normalize inverse
    //
    dft_f /= 4;

    cout << endl << "The DFT of f is: "<<dft_f<<endl;

    //Get magnitude:
    //
    //  magnitude = sqrt(real^2 + imaginary^2)
    //
    float magnitude[4];
    int m_index = 0;

    for (int i = 0; i < 8; i = i + 2)
    {
        magnitude[m_index] = sqrt(pow(dft_f.at<float>(0,i), 2.0) + pow(dft_f.at<float>(0,i+1), 2.0));
        m_index++;
    }

    //Do inverse transformation.
    //
    dft(dft_f, dft_f, DFT_INVERSE);

    cout << endl << "Inverse of DFT is: "<< dft_f << endl << endl;



    return 0;
}