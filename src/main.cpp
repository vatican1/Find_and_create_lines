#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include "Gaussian_blur.h"
#include "Sobel.h"

void redraw(){

}

int main() {
    cv::Mat src1 = cv::imread("data/Helsinki_1.JPEG");
    cv::Mat src2 = cv::imread("data/Helsinki_2.JPEG");
    if (src1.empty()) {
        std::cout << "Error loading src1 \n";
        return -1;
    }
    if (src2.empty()) {
        std::cout << "Error loading src2 \n";
        return -1;
    }

    namedWindow("My Window", cv::WINDOW_NORMAL);

    auto* data = new GaussianBlurData(0, 1, &src1);

    cv::createTrackbar("Gaussian blur sigma", "My Window", &data->sigma, 100,
                       MyCallbackForGaussianBlurSigma, data);
    cv::createTrackbar("Gaussian blur kSize", "My Window", &data->kSize, 10,
                       MyCallbackForGaussianBlurKSizeXY, data);

    cv::Mat srcBlurGray1;
    while (true) {
        cv::cvtColor(data->dst, srcBlurGray1, cv::COLOR_BGR2GRAY);

        cv::Mat grad;

        cv::Mat grad_x, grad_y;
        cv::Mat abs_grad_x, abs_grad_y;

        cv::Sobel(srcBlurGray1, grad_x, CV_16S, 1, 0);
        cv::Sobel(srcBlurGray1, grad_y, CV_16S, 0, 1);

        convertScaleAbs(grad_x, abs_grad_x);
        convertScaleAbs(grad_y, abs_grad_y);
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

        cv::namedWindow("Sobel_dx", cv::WINDOW_NORMAL);
        cv::namedWindow("Sobel_dy", cv::WINDOW_NORMAL);
        imshow("Sobel_dx", abs_grad_x);
        imshow("Sobel_dy", abs_grad_y);

        cv::namedWindow("Sobel", cv::WINDOW_NORMAL);
        imshow("Sobel", grad);

        cv::waitKey(0);
    }

    return 0;
}
