
#include "opencv2/opencv.hpp"
#include "TrackbarsData.h"
#include "mainInclude.h"


GaussianBlurData::GaussianBlurData(int sigma, int kSize, cv::Mat *src, std::string winName) : sigma(sigma),
                                                                                              kSize(kSize), src(src),
                                                                                              winName(winName) {
    dst = src->clone();
}

cv::Size GaussianBlurData::getKSize() {
    return cv::Size{2 * kSize + 1, 2 * kSize + 1};
}

double GaussianBlurData::getSigma() {
    return (double) sigma / 10;
}

void GaussianBlurData::redraw() {
    if (sigma != 0 && kSize != 0) {
        cv::GaussianBlur(*src, dst, this->getKSize(), this->getSigma());
        imshow("Blur", dst);
    } else {
        dst = src->clone();
        imshow("Blur", dst);

    }
}


void GaussianBlurData::MyCallbackForGaussianBlurSigma(int sigmaTrackbar, void *userData) {
    auto data = *(static_cast<AllTransforms *>(userData));
    data.redraw();
}

void GaussianBlurData::MyCallbackForGaussianBlurKSizeXY(int kSizeXY, void *userData) {
    auto data = *(static_cast<AllTransforms *>(userData));
    data.redraw();
}



