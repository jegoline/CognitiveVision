/*
 * ImagePyramid.cpp
 *
 *  Created on: 25-Apr-2017
 *      Author: Barykina
 */

#include "ImagePyramid.h"

ImagePyramid::ImagePyramid(cv::Mat& image, int number_of_layers, float sigma) {
	cv::Mat blurred;
	cv::Mat current = image.clone();

	for (int k = 0; k < number_of_layers; k++) {
		cv::GaussianBlur(current, blurred, cv::Size(), sigma, sigma,
				cv::BORDER_REPLICATE);
		layers_.push_back(blurred.clone());
		cv::resize(current, current, cv::Size(), 0.5, 0.5, cv::INTER_NEAREST);
	}
}

ImagePyramid::ImagePyramid(ImagePyramid& pyramid, float sigma) {
	for (int i = 0; i < pyramid.numOfLayers(); i++) {
		cv::Mat image = pyramid.get(i).clone();

		cv::GaussianBlur(image, image, cv::Size(), sigma, sigma,
						cv::BORDER_REPLICATE);
		layers_.push_back(image);
	}
}

int ImagePyramid::numOfLayers() const {
	return layers_.size();
}

cv::Mat ImagePyramid::get(int layer) const {
	return layers_[layer];
}

ImagePyramid::~ImagePyramid() {
}

