/*
 * ImagePyramid.h
 *
 *  Created on: 25-Apr-2017
 *      Author: Barykina
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdio.h>

#ifndef IMAGEPYRAMID_H_
#define IMAGEPYRAMID_H_

class ImagePyramid {
public:
	ImagePyramid(cv::Mat& image, int number_of_layers);
	virtual ~ImagePyramid();
	cv::Mat get(int layer);

private:
	std::vector<cv::Mat> layers_;
};

#endif /* IMAGEPYRAMID_H_ */
