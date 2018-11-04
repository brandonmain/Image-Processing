#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace cv;
using namespace std;


int main (int argc, char** argv)
{
    //Put sample of function into file
    //
    float buffer[128];

    ofstream fout("cos.csv");

    for(int i = 0; i < 128; i++)
    {
        buffer[i] = cos(((2 * 3.14) * 8 * i )/ 128);
        fout << i << ',' << buffer[i] << endl;
    }

    fout.close();

    //Put dft of samples into file
    //
    Mat f = (Mat_<float>(1,128));

    for (int i = 0; i < 128; ++i)
    {
        f.at<float>(0,i) = buffer[i];
    }

    Mat dft_f;
    dft(f, dft_f, DFT_COMPLEX_OUTPUT);

    //Normalize DFT
    dft_f /= 128;

    //Plot real part of dft
    //
    fout.open("dft_real.csv");

    int count = 0;

    for (int i = 0; i < 256; i = i + 2)
    {
        fout << count << ',' << dft_f.at<float>(0,i) << endl;
        count++;
    }

    fout.close();

    //Get magnitude:
    //
    //  magnitude = sqrt(real^2 + imaginary^2)
    //
    float magnitude[128];
    int m_index = 0;


    for (int i = 0; i < 128; i = i + 2)
    {
        dft_f.at<float>(0,i) = floor(dft_f.at<float>(0,i));
        dft_f.at<float>(0,i+1) = floor(dft_f.at<float>(0,i+1));
        magnitude[m_index] = sqrt(pow(dft_f.at<float>(0,i), 2) + pow(dft_f.at<float>(0,i+1), 2));
        //cout << magnitude[m_index] << endl;
        m_index++;
    }
    
    fout.open("dft_magnitude.csv");

    for (int i = 0; i < 128; ++i)
    {
        fout << i << ',' << magnitude[i] << endl;
    }


    fout.close();
    
    //Plot imaginary part of dft
    //
    fout.open("dft_imaginary.csv");

    count = 0;

    for (int i = 1; i < 256; i = i + 2)
    {
        fout << count << ',' << dft_f.at<float>(0,i) << endl;
        count++;
    }

    fout.close();

    //Get phase 
    //
    fout.open("phase.csv");

    float phase = 0;
    count = 0;

    for (int i = 0; i < 256; i = i + 2)
    {
        phase = atan2(dft_f.at<float>(0,i), dft_f.at<float>(0,i+1));
        fout << count << ',' << phase << endl;
    }




    return 0;
}