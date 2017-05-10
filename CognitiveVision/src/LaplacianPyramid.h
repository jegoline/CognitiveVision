/*
 * LaplacianPyramid.h
 *
 *  Created on: 09-May-2017
 *      Author: Barykina
 */

#ifndef SRC_LAPLACIANPYRAMID_H_
#define SRC_LAPLACIANPYRAMID_H_

#include "ImagePyramid.h"

class LaplacianPyramid {
public:
	LaplacianPyramid(const ImagePyramid & p , float sigma);
	virtual ~LaplacianPyramid();
	cv::Mat get(int layer) const;
	int numOfLayers() const;
private:
	std::vector<cv::Mat> layers_;
};

#endif /* SRC_LAPLACIANPYRAMID_H_ */
