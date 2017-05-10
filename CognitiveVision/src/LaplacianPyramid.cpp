/*
 * LaplacianPyramid.cpp
 *
 *  Created on: 09-May-2017
 *      Author: Barykina
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>

#include <stdio.h>
#include <iostream>
#include "ImagePyramid.h"

#include "LaplacianPyramid.h"

LaplacianPyramid::LaplacianPyramid(const ImagePyramid & p , float sigma){
	for (int i = 0; i < p.numOfLayers(); i++){
		cv::Mat layer = p.get(i);

		cv::Mat dst = layer.clone();
		cv::GaussianBlur(dst, dst, cv::Size(), sigma, sigma,
						cv::BORDER_REPLICATE);
		dst = dst - layer;
		layers_.push_back(dst);
	}
}

int LaplacianPyramid::numOfLayers() const{
	return layers_.size();
}

cv::Mat LaplacianPyramid::get(int layer) const {
	return layers_[layer];
}

LaplacianPyramid::~LaplacianPyramid() {

}

