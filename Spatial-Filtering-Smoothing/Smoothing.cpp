/**
 * Spatial Filtering (Smoothing)
 * 
 * @brief This program will smooth an image
 *        
 * Usage:  ~$ ./Smoothing image.pgm
 *  
 */  

#include "imageLib.h"
#include <fstream>

Mat addPadding(Mat &image, const int SIZE);
Mat crop(Mat &image, const int SIZE);
Mat setMaskWeights(const int SIZE);
Mat convolve(Mat &image, Mat &filter);
void avg7x7(Mat &image);
void avg15x15(Mat &image);
void gaussian7x7(Mat &image);
void gaussian15x15(Mat &image);



int main(int argc, char** argv)
{

	Mat image = imread(argv[1], IMREAD_GRAYSCALE);

	int choice = 0;

	cout << endl << "Enter your choice:" << endl;
	cout << "1. Smooth using 7x7 averaging filter." << endl;
	cout << "2. Smooth using 15x15 averaging filter." << endl;
	cout << "3. Smooth using 7x7 gaussian filter." << endl;
	cout << "4. Smooth using 15x15 gaussian filter." << endl;
	cin >> choice;

	switch(choice)
	{
		case 1: //7x7 avg
		{
			avg7x7(image);
			break;
		}
		case 2: //15x15 avg
		{
			avg15x15(image);
			break;
		}
		case 3: //7x7 gaussian
		{
			gaussian7x7(image);
			break;
		}
		case 4: //15x15 gaussian
		{
			gaussian15x15(image);
			break;
		}
	}
	return 0;
}


Mat addPadding(Mat &image, const int SIZE)
{
	Mat new_image(image.rows + 2*(SIZE - 1), image.cols + 2*(SIZE - 1), CV_8U);

	//Add 0 padding
	for (int i = 0; i < new_image.rows; ++i)
	{
		for (int j = 0; j < new_image.cols; ++j)
		{
			new_image.at<unsigned char>(i,j) = 0;
		}
	}

	for (int i = SIZE - 1; i < new_image.rows - SIZE - 1; ++i)
	{
		for (int j = SIZE - 1; j < new_image.rows - SIZE - 1; ++j)
		{
			new_image.at<unsigned char>(i,j) = image.at<unsigned char>(i - (SIZE - 1), j - (SIZE - 1));
		}	
	}

	return new_image;
}

Mat crop(Mat &image, const int SIZE)
{
	Mat new_image(image.rows - 2*(SIZE+1), image.cols - 2*(SIZE+1), CV_8U);

	for (int i = 0; i < new_image.rows; ++i)
	{
		for (int j = 0; j < new_image.cols; ++j)
		{
			new_image.at<unsigned char>(i,j) = image.at<unsigned char>(i + SIZE - 1, j + SIZE - 1);
		}
	}

	return new_image;
}

void avg7x7(Mat &image)
{
	Mat padded_image(addPadding(image, 7));
	Mat averaged_image(padded_image.rows, padded_image.cols, CV_8U);
	int sum = 0;

	//Loop over entire image
    for (int pad_rows = 0; pad_rows < padded_image.rows; ++pad_rows)
    {
        for (int pad_cols = 0; pad_cols < padded_image.cols; ++pad_cols)
        {
            //Loop over mask
            for (int i = 0; i < 7; ++i)
            {
                for (int j = 0; j < 7; ++j)
                {
                    sum += image.at<unsigned char>(pad_rows + i, pad_cols + j);
                }
            }
            averaged_image.at<unsigned char>(pad_rows,pad_cols) = sum/49;
            sum = 0;
        }
    }

    Mat cropped_image(crop(averaged_image, 7));
    displayIMG("original", image);
    displayIMG("Smoothed 7x7 avg", cropped_image);


}

void avg15x15(Mat &image)
{
	Mat padded_image(addPadding(image, 15));
	Mat averaged_image(padded_image.rows, padded_image.cols, CV_8U);
	int sum = 0;

	//Loop over entire image
    for (int pad_rows = 0; pad_rows < padded_image.rows; ++pad_rows)
    {
        for (int pad_cols = 0; pad_cols < padded_image.cols; ++pad_cols)
        {
            //Loop over mask
            for (int i = 0; i < 15; ++i)
            {
                for (int j = 0; j < 15; ++j)
                {
                    sum += image.at<unsigned char>(pad_rows + i, pad_cols + j);
                }
            }
            averaged_image.at<unsigned char>(pad_rows,pad_cols) = sum/225;
            sum = 0;
        }
    }

    Mat cropped_image(crop(averaged_image, 15));
    displayIMG("original", image);
    displayIMG("Smoothed 15x15 avg", cropped_image);

}

Mat setMaskWeights(const int SIZE)
{
	ifstream fin;

	if(SIZE == 7)
	{
		fin.open("7.txt");
	}
	else if(SIZE == 15)
	{
		fin.open("15.txt");
	}

	//Read file data into mask
	Mat mask(SIZE, SIZE, CV_32F);

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			fin >> mask.at<float>(i,j);
		}
	}

	//Get the sum
	float sum = 0;

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			sum += mask.at<float>(i,j);
		}
	}
	cout << "Sum:" << sum;


	//Normalize
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			mask.at<float>(i,j) /= sum;
		}
	}

	fin.close();

	return mask;
}
void gaussian7x7(Mat &image)
{
	/*
	Mat padded_image(addPadding(image, 7));
	Mat mask(setMaskWeights(7));
	Mat averaged_image(padded_image.rows, padded_image.cols, CV_32F);
	float sum;

	//Loop over entire image
    for (int pad_rows = 0; pad_rows < padded_image.rows; ++pad_rows)
    {
        for (int pad_cols = 0; pad_cols < padded_image.cols; ++pad_cols)
        {
            //Loop over mask
            for (int i = 0; i < 7; ++i)
            {
                for (int j = 0; j < 7; ++j)
                {
                    sum += mask.at<float>(i,j) * padded_image.at<float>(pad_rows + i, pad_cols + j);
                }
            }
            averaged_image.at<float>(pad_rows,pad_cols) = sum;
            cout << sum << " ";
            sum = 0;
        }
    }

    //Mat cropped_image(crop(averaged_image, 15));
    //displayIMG("original", image);
    //displayIMG("Smoothed 15x15 avg", averaged_image);

*/
	ifstream fin;
	fin.open("7.txt");

	Mat gaussian;

	for(int i = 0; i < 7; i++)
    {
    	for(int j = 0; j < 7; j++)
    	{
    		fin >> gaussian.at<int>(i,j);
    	}
    }

	Mat normalized_gaussian;
	normalized_gaussian = gaussian/136.0;
	/*
    for(int i = 0; i < 7; i++)
    {
    	for(int j = 0; j < 7; j++)
    	{
    		normalized_gaussian = gaussian/136.0;
    	}
    }
*/
    Mat gaussian_7 = convolve(image, normalized_gaussian);

    displayIMG("7x7", gaussian_7);
}

Mat convolve(Mat &image, Mat &filter)

{// find center position of kernel (half of kernel size)
	int imgRows = image.rows;
	int imgCols = image.cols;

	int fRows = filter.rows;
	int fCols = filter.cols;

	int fCenterX = (fRows-1) / 2;
	int fCenterY = (fCols-1) / 2;

	Mat output = image.clone();


	for (int i=fCenterX; i<(imgRows-fCenterX); i++)
	{
		for (int j=fCenterY; j<(imgCols-fCenterY); j++)
		{
			int sum = 0;

			for (int k=-fCenterX; k<(fCenterX+1); k++)
			{
				for (int l=-fCenterY; l<(fCenterY+1); l++)
				{
					sum += filter.at<double>(fCenterX+k,fCenterY+l) * image.at<uchar>(k+i,l+j);
					sum = sum > 255 ? 255:sum;
					sum = sum < 0 ? 0 : sum;
				}
			}

			output.at<uchar>(i,j) = saturate_cast<uchar>(sum);
		}
	}
	return output;
}

void gaussian15x15(Mat &image)
{

}
