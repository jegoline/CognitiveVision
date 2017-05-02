#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdio.h>
#include <iostream>

int main(int argc, char** argv) {
	cv::Mat mt = cv::Mat::ones(3, 3, CV_32F);
	mt.at<float>(1, 1) = 2.0;
	std::cout << "Matrix = " << std::endl << " " << mt << std::endl << std::endl;

	float kernel_data[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
	cv::Mat kernel(3, 3, CV_32F, kernel_data);
	kernel = kernel/16;
	cv::Mat rs = cv::Mat::zeros(3, 3, CV_32F);

	cv::filter2D(mt, rs, -1, kernel, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	std::cout << "Kernel = " << std::endl << " " << kernel << std::endl << std::endl;
	std::cout << "Convoluted: = " << std::endl << " " << rs << std::endl << std::endl;

	float kernel_data_1d [] = {1, 2, 1};
	cv::Mat kernel_1d(3, 1, CV_32F, kernel_data_1d);
	kernel_1d = kernel_1d/4;

	cv::Mat kernel_1d_tr = cv::Mat::zeros(1, 3, CV_32F);
	cv::transpose(kernel_1d, kernel_1d_tr);

	std::cout << "Kernel = " << std::endl << " " << kernel_1d << std::endl << std::endl;
	std::cout << "Transposed = " << std::endl << " " << kernel_1d_tr << std::endl << std::endl;

	cv::filter2D(mt, rs, -1, kernel_1d, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	cv::filter2D(rs, rs, -1, kernel_1d_tr, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	std::cout << "Convoluted: = " << std::endl << " " << rs << std::endl << std::endl;

	//GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT )
	cv::GaussianBlur(mt, rs, cv::Size(3,3), 2, 2,cv:: BORDER_CONSTANT);
	std::cout << "Gaussian Blur: = " << std::endl << " " << rs << std::endl << std::endl;

	cv::Mat image = cv::imread("p_and_p.jpg", 1);
	//cv::imshow("Image", image);
	//cv::waitKey(700);

	//for (int k = 3; k < 11; k+=2){
		//cv::GaussianBlur(image, image, cv::Size(k,k), 2, 2,cv:: BORDER_CONSTANT);
		//cv::imshow("Image", image);
		//cv::waitKey(700);
	//}

	cv::Mat image_gray = image.clone();
	cv::cvtColor (image , image_gray , cv :: COLOR_BGR2GRAY);
	image_gray.convertTo(image_gray, CV_32F);

	cv::Mat image_gray_1 = image.clone();
	cv::Mat image_gray_2 = image.clone();

	cv::GaussianBlur(image_gray, image_gray_1, cv::Size(3,3), 1, 1, cv:: BORDER_CONSTANT);
	cv::GaussianBlur(image_gray, image_gray_2, cv::Size(3,3), 3, 3, cv:: BORDER_CONSTANT);

	//cv::imshow("Image", (image_gray_1 - image_gray_2));
	//cv::waitKey(10000);
}
