#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<math.h>

#include <stdio.h>
#include <iostream>
#include "ImagePyramid.h"
#include "LaplacianPyramid.h"
#include "OrientedPyramid.h"

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
	cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	cv::imshow("Original", image);
	cv::waitKey(0);

	ImagePyramid gaussian_pyramid(image, 5, 1);
	LaplacianPyramid laplacian_pyramid(gaussian_pyramid, 4);
	OrientedPyramid oriented_pyramid(laplacian_pyramid, 8);

	for (int i = 0; i < oriented_pyramid.numOfOrientations(); ++i) {
		std::vector<cv::Mat> scales;
		for (int j = 0; j < oriented_pyramid.numOfLayers(); ++j) {
			scales.push_back(oriented_pyramid.get(j, i));
		}
		cv::imshow("Filtered", across_scale_addition(scales));
		cv::waitKey(0);
	}
}
