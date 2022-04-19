#ifndef FIND_AND_CREATE_LINES_GAUSSIAN_BLUR_H
#define FIND_AND_CREATE_LINES_GAUSSIAN_BLUR_H

#include "opencv2/opencv.hpp"
#include "Gaussian_blur.h"
#include "opencv2/opencv.hpp"

class GaussianBlurData {
public:
    cv::Mat *src;

    GaussianBlurData(int sigma, int kSize, cv::Mat *src) : sigma(sigma), kSize(kSize), src(src) {
        dst = src->clone();
    }
    cv::Size getKSize(){
        return cv::Size{2 * kSize + 1, 2 * kSize + 1};
    }
    double getSigma(){
        return (double) sigma / 10;
    }
    cv::Mat dst;
    int sigma;
    int kSize;
};

void MyCallbackForGaussianBlurSigma(int sigmaTrackbar, void *userData);


void MyCallbackForGaussianBlurKSizeXY(int kSizeXY, void *userData);

void gaussianBlur(cv::Mat src);

#endif
