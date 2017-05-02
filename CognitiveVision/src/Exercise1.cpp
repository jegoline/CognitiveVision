#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdio.h>
#include <iostream>

using namespace cv;

int main(int argc, char** argv) {
	cv::Mat c =
			(cv::Mat_<uchar>(4, 4) << 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

	std::cout << "C = " << std::endl << " " << c << std::endl << std::endl;

	std::cout << c.at<uchar>(1, 2);
	c.at<uchar>(1, 2) = 0;
	std::cout << c.at<uchar>(1, 2);

	std::cout << "C = " << std::endl << " " << c << std::endl << std::endl;

	int channels = c.channels();

	int nRows = c.rows;
	int nCols = c.cols * channels;

	int i, j;
	uchar* p;

	for (i = 0; i < nRows; ++i) {
		for (j = 0; j < nCols; ++j) {
			std::cout << static_cast<int>(c.at<uchar>(i, j));
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	cv::Mat copy = cv::Mat(c);
	c.at<uchar>(1, 2) = 100;

	std::cout << "c = " << std::endl << " " << c << std::endl << std::endl;
	std::cout << "m = " << std::endl << " " << copy << std::endl << std::endl;

	cv::Mat blue = Mat::zeros(25, 25, CV_8UC3);

	channels = blue.channels();
	nRows = blue.rows;
	nCols = blue.cols * channels;

    for( i = 0; i < nRows; ++i)
    {
        p = blue.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
        	if(j % 3 == 0){
        		p[j] = 255;
        	}
        }
    }

	// std::cout << "blue = " << std::endl << " " << blue << std::endl << std::endl;

	imshow("Blue", blue);
	waitKey(0);
}
