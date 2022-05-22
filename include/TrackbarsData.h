#ifndef FIND_AND_CREATE_LINES_GAUSIANBLUR_H
#define FIND_AND_CREATE_LINES_GAUSIANBLUR_H

#include "opencv2/opencv.hpp"
#include "opencv2/opencv.hpp"

class GaussianBlurData {
public:
    cv::Mat *src;
    cv::Mat dst;
    int sigma, kSize;
    std::string winName;

    GaussianBlurData(int sigma, int kSize, cv::Mat *src, std::string winName);

    cv::Size getKSize();

    double getSigma();

    void redraw();

    static void MyCallbackForGaussianBlurSigma(int sigmaTrackbar, void *userData);

    static void MyCallbackForGaussianBlurKSizeXY(int kSizeXY, void *userData);
};


#endif
