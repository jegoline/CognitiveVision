#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>

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

cv::Mat mean_fusion(const cv::Mat& f1, const cv::Mat& f2, double w1 = 1.0,
		double w2 = 1.0) {
	cv::Mat resized = f1;

	if (f1.size() != f2.size()) {
		resized = f1.clone();
		cv::resize(resized, resized, f2.size(), 0, 0, cv::INTER_CUBIC);
	}

	cv::Mat ret = cv::Mat::zeros(f2.size(), CV_32F);
	ret = (w1 * resized + w2 * f2) / (w1 + w2);
	return ret;
}

// for max fusion multiply to wights BEFORE (to get proper normalization)
cv::Mat max_fusion(const cv::Mat& f1, const cv::Mat& f2) {
	cv::Mat resized = f1;

	if (f1.size() != f2.size()) {
		resized = f1.clone();
		cv::resize(resized, resized, f2.size(), 0, 0, cv::INTER_CUBIC);
	}

	cv::Mat ret = cv::Mat::zeros(f2.size(), CV_32F);
	ret = cv::max(resized, f2);
	return ret;
}

int main(int argc, char** argv) {
	cv::Mat image = cv::imread("p_and_p.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//	cv::imshow("Original", image);
//	cv::waitKey(0);

	cv::normalize(image, image, 0.0, 1.0, cv::NORM_MINMAX);
	double minVal = 0;
	double maxVal = 0;
	cv::minMaxLoc(image, &minVal, &maxVal);
	std::cout << minVal << std::endl;
	std::cout << maxVal << std::endl;

	std::vector<cv::Mat> on_off(10);
	std::vector<cv::Mat> off_on(10);
	for (int i = 0; i < 10; ++i) {
		std::stringstream ss;
		ss << i;
		std::string i_as_str = ss.str();

		std::string off_on_filename = "../contrasts/off_on_L_" + i_as_str
				+ ".png";
		off_on[i] = cv::imread(off_on_filename.c_str(),
				CV_LOAD_IMAGE_GRAYSCALE);
		off_on[i].convertTo(off_on[i], CV_32F);

		std::string on_off_filename = "../contrasts/on_off_L_" + i_as_str
				+ ".png";
		on_off[i] = cv::imread(on_off_filename.c_str(),
				CV_LOAD_IMAGE_GRAYSCALE);
		on_off[i].convertTo(on_off[i], CV_32F);

//        cv::namedWindow(off_on_filename.c_str(), CV_WINDOW_NORMAL);
//        cv::imshow(off_on_filename.c_str(), off_on[i]);
//        cv::namedWindow(on_off_filename.c_str(), CV_WINDOW_NORMAL);
//        cv::imshow(on_off_filename.c_str(), on_off[i]);
//
//        cv::waitKey(0);
//        cv::destroyWindow(off_on_filename.c_str());
//        cv::destroyWindow(on_off_filename.c_str());
	}

	std::cout << "Constructing across-scale feature maps" << std::endl;
	cv::Mat on_off_map = across_scale_addition(on_off);
	cv::Mat off_on_map = across_scale_addition(off_on);

	cv::Mat max_f = max_fusion(on_off_map, off_on_map);
	cv::Mat mean_f = mean_fusion(on_off_map, off_on_map, 2.0, 1.0);

	double minVal1 = 0;
	double maxVal1 = 0;
	double minVal2 = 0;
	double maxVal2 = 0;

	cv::minMaxLoc(max_f, &minVal1, &maxVal1);
	cv::minMaxLoc(mean_f, &minVal2, &maxVal2);

	cv::normalize(max_f, max_f, 0.0, std::max(maxVal2, maxVal1),
			cv::NORM_MINMAX);
	cv::normalize(mean_f, mean_f, 0.0, std::max(maxVal2, maxVal1),
			cv::NORM_MINMAX);

	cv::Mat max_f_copy = max_f.clone();
	cv::normalize(max_f_copy, max_f_copy, 0.0, 1, cv::NORM_MINMAX);

	cv::Mat mean_f_copy = mean_f.clone();
	cv::normalize(mean_f_copy, mean_f_copy, 0.0, 1, cv::NORM_MINMAX);

	cv::imshow("Mean Fusion", mean_f_copy);
	cv::imshow("Max Fusion", max_f_copy);

	cv::waitKey(0);

	return 0;
}
