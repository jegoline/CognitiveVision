/*
 * OrientedPyramid.h
 *
 *  Created on: 09-May-2017
 *      Author: Barykina
 */

#ifndef SRC_ORIENTEDPYRAMID_H_
#define SRC_ORIENTEDPYRAMID_H_

#include <opencv2/core/mat.hpp>
#include <vector>

class LaplacianPyramid;

class OrientedPyramid {
public:
	OrientedPyramid(const LaplacianPyramid & p, int num_orientations);
	OrientedPyramid(const LaplacianPyramid & p, std::vector<cv::Mat> & gaborFilters);
	virtual ~OrientedPyramid();

	cv::Mat get(int layer, int orientation) const;

	int numOfLayers() const;
	int numOfOrientations() const;

private:
	std::vector< std::vector<cv::Mat> > orientation_maps_;
	void init(const LaplacianPyramid & p, std::vector<cv::Mat> & gaborFilters);
};

#endif /* SRC_ORIENTEDPYRAMID_H_ */
