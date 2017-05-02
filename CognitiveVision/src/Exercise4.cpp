#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<math.h>

#include <stdio.h>
#include <iostream>
#include "ImagePyramid.h"

cv::Mat across_scale_addition(const std::vector<cv::Mat>& scale_images) {
	cv::Mat f = cv::Mat::zeros(scale_images[0].size(), CV_32F);

	for (int j = 0; j < scale_images.size(); ++j) {
		cv::Mat image = scale_images[j].clone();
		cv::resize(image, image, scale_images[0].size(), 0, 0, cv::INTER_CUBIC);
		f = f + image;
	}

	return f;
}

int main(int argc, char** argv) {
	cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
	cv::Mat image_lab;
	cv::imshow("Original", image);

	cv::cvtColor(image, image_lab, cv::COLOR_BGR2Lab);
	image_lab.convertTo(image_lab, CV_32FC3);

	std::vector<cv::Mat> splitted_channels;
	cv::split(image_lab, splitted_channels);

	int num_of_layers = 4;

	for (int i = 0; i < 3; ++i) {
		ImagePyramid lCenterPyr(splitted_channels[i], num_of_layers, 2);
		ImagePyramid lSurrPyr(lCenterPyr, sqrt(5));

		std::vector<cv::Mat> scaled_images_cs;
		std::vector<cv::Mat> scaled_images_sc;

		for (int j = 0; j < num_of_layers; ++j) {
			cv::Mat center = lCenterPyr.get(j);
			cv::Mat surround = lSurrPyr.get(j);

			cv::Mat cs = surround - center;
			cv::Mat sc = center - surround;

			cv::threshold(cs, cs, 0, 1, cv::THRESH_TOZERO);
			cv::threshold(sc, sc, 0, 1, cv::THRESH_TOZERO);

			//cv::imshow("Center-surround", cs);
			//cv::imshow("Surround-center", sc);

			//std::cout << "Displaying layer " << i << " of b channel pyramid" << std::endl;
			//cv::waitKey(0);
			scaled_images_cs.push_back(cs);
			scaled_images_sc.push_back(sc);
		}
		cv::imshow("Center-surround", across_scale_addition(scaled_images_cs));
		cv::imshow("Surround-center", across_scale_addition(scaled_images_sc));
		cv::waitKey(0);
	}
}
