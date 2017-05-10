/*
 * OrientedPyramid.cpp
 *
 *  Created on: 09-May-2017
 *      Author: Barykina
 */

#include "OrientedPyramid.h"

#include <opencv2/core/cvdef.h>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.inl.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "LaplacianPyramid.h"

OrientedPyramid::OrientedPyramid(const LaplacianPyramid & p,
		int num_orientations) {
	double theta = 0;
	std::vector<cv::Mat> gaborFilters;

	for (int j = 0; j < num_orientations; ++j) {
		cv::Mat kernel = cv::getGaborKernel(cv::Size(6, 6), 1, theta, 2, 1.0,
				0.0, CV_32F);
		gaborFilters.push_back(kernel);
		theta += CV_PI / num_orientations;
	}
	init(p, gaborFilters);

}

OrientedPyramid::OrientedPyramid(const LaplacianPyramid & p,
		std::vector<cv::Mat> & gaborFilters) {
	init(p, gaborFilters);
}

void OrientedPyramid::init(const LaplacianPyramid & p,
		std::vector<cv::Mat> & gaborFilters) {
	for (int i = 0; i < p.numOfLayers(); i++) {
		cv::Mat layer = p.get(i);
		std::vector<cv::Mat> orientations;
		for (int j = 0; j < gaborFilters.size(); j++) {
			cv::Mat dst = layer.clone();
			cv::filter2D(dst, dst, CV_32F, gaborFilters[j]);
			orientations.push_back(dst);
		}

		orientation_maps_.push_back(orientations);
	}
}

cv::Mat OrientedPyramid::get(int layer, int orientation) const {
	return orientation_maps_[layer][orientation];
}

int OrientedPyramid::numOfLayers() const {
	return orientation_maps_.size();
}

int OrientedPyramid::numOfOrientations() const {
	return orientation_maps_[0].size();
}

OrientedPyramid::~OrientedPyramid() {
}

