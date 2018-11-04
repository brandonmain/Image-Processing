/**
 * Median Filtering
 * 
 * @brief This program will smooth an image
 *        
 * Usage:  ~$ ./Median image.pgm
 *  
 */ 
#include "imageLib.h"
#include <cstdlib>
#include <algorithm>


Mat corrupt(Mat &image);
Mat median(Mat &image);

 int main()
 {
 	Mat lenna = imread("lenna.pgm", IMREAD_GRAYSCALE);

 	Mat corrupted_lenna(corrupt(lenna));
 	displayIMG("",corrupted_lenna);

 	Mat filtered_lenna(median(corrupted_lenna));
 	displayIMG("", filtered_lenna);


 	return 0;
 } 


 Mat corrupt(Mat &image)
 {
 	Mat saltpepper_noise = Mat::zeros(image.rows, image.cols,CV_8U);
	randu(saltpepper_noise,0,255);

	Mat black = saltpepper_noise < 30;
	Mat white = saltpepper_noise > 225;

	Mat saltpepper_img = image;
	saltpepper_img.setTo(255,white);
	saltpepper_img.setTo(0,black);


 	return saltpepper_img;

}

Mat median(Mat &image)
{
	Mat new_image(image.rows, image.cols, CV_8U);

	//7x7
	for (int i = 7; i < image.rows; ++i)
	{
		for (int j = 7; j < image.cols; ++j)
		{
			//Find median
			int array[49];
			int index = 0;
			for (int m = 0; m < 7; ++m)
			{
				for (int n = 0; n < 7; ++n)
				{
					array[index] = image.at<int>(i - 7 + m, j - 7 + n);
					index++;
				}
			}
			sort(array, array + 49);
			new_image.at<int>(i-7,j-7) = array[49/2];
		}
	}


	return new_image;
}


