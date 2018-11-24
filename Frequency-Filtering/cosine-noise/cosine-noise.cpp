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

	Mat original_image = imread(argv[1], IMREAD_GRAYSCALE);

	imshow("original", original_image);

	// Wait for a keystroke in the WINDOW
    waitKey(0);

	return 0;
}