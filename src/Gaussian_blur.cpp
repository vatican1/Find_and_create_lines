#include "Gaussian_blur.h"
#include "opencv2/opencv.hpp"


void MyCallbackForGaussianBlurSigma(int sigmaTrackbar, void *userData) {
    printf("start sigma\n");
    auto data = *(static_cast<GaussianBlurData *>(userData));
    cv::Mat src = *data.src;

    if (sigmaTrackbar != 0 && data.kSize != 0) {
        double sigma = (double) sigmaTrackbar / 10;
        printf("sigma = %f, ksize = %d\n", sigma, data.getKSize());
        cv::GaussianBlur(src, data.dst, data.getKSize(), sigma);

    } else {
        data.dst = src.clone();
    }
    imshow("My Window", data.dst);
}

void MyCallbackForGaussianBlurKSizeXY(int kSizeXY, void *userData) {
    printf("Start kSize\n");
    auto data = *(static_cast<GaussianBlurData *>(userData));
    cv::Mat src = *data.src;

    if (kSizeXY != 0 && data.sigma != 0) {
        kSizeXY = kSizeXY * 2 + 1;
        printf("sigma = %d, ksize = %d\n", data.sigma, kSizeXY);
        cv::GaussianBlur(src, data.dst, cv::Size{kSizeXY, kSizeXY}, data.getSigma());
    } else{
        data.dst = src.clone();
    }
    imshow("My Window", data.dst);
}

void gaussianBlur(cv::Mat src) {

}