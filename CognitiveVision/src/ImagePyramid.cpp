/*
 * ImagePyramid.cpp
 *
 *  Created on: 25-Apr-2017
 *      Author: Barykina
 */

#include "ImagePyramid.h"


ImagePyramid::ImagePyramid(cv::Mat& image, int number_of_layers) {
	cv::Mat blurred;
	cv::Mat current = image.clone();

	for (int k = 0; k < number_of_layers; k++) {
		cv::GaussianBlur(current, blurred, cv::Size(5, 5), 0, 0,
				cv::BORDER_CONSTANT);
		layers_.push_back(blurred.clone());
		cv::resize(current, current, cv::Size(), 0.5, 0.5,
				cv::INTER_NEAREST);
	}
}

cv::Mat ImagePyramid::get(int layer) {
	return layers_[layer];
}

ImagePyramid::~ImagePyramid() {
}

