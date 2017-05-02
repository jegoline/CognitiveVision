#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdio.h>
#include <iostream>
#include "ImagePyramid.h"

int main(int argc, char** argv) {
	cv::Mat image = cv::imread("p_and_p.jpg", CV_LOAD_IMAGE_COLOR);
	cv::Mat image_lab;

	cv::cvtColor (image, image_lab , cv :: COLOR_BGR2Lab);

	std::cout << "Image converted to Lab" << std::endl;

	image_lab.convertTo(image_lab, CV_32FC3);
	image_lab /= 255.0f;

	std::cout << "Image converted to Lab" << std::endl;

	std::vector<cv::Mat> splitted_channels;
	cv::split(image_lab, splitted_channels);

	std::cout << "Image splitted to channels" << std::endl;

	int num_of_layers = 4;

	ImagePyramid pyramid1(splitted_channels[0], num_of_layers);
	ImagePyramid pyramid2(splitted_channels[1], num_of_layers);
	ImagePyramid pyramid3(splitted_channels[2], num_of_layers);

	std::cout << "Image pyramids are builded" << std::endl;

    for (int i = 0; i < num_of_layers; ++i)
    {
        cv::imshow("Pyramid for L channel", pyramid1.get(i) );
        std::cout << "Displaying layer " << i << " of L channel pyramid" << std::endl;
        int c = cv::waitKey(0);
    }

    for (int i = 0; i < num_of_layers; ++i)
    {
        cv::imshow("Pyramid for a channel", pyramid2.get(i) );
        std::cout << "Displaying layer " << i << " of a channel pyramid" << std::endl;
        int c = cv::waitKey(0);
    }

    // b pyramid
    for (int i = 0; i <num_of_layers; ++i)
    {
        cv::imshow("Pyramid for b channel", pyramid3.get(i) );
        std::cout << "Displaying layer " << i << " of b channel pyramid" << std::endl;
        int c = cv::waitKey(0);
    }
}
