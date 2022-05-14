
#include "opencv2/opencv.hpp"
#include "TrackbarsData.h"

GaussianBlurData::GaussianBlurData(int sigma, int kSize, cv::Mat *src) : sigma(sigma), kSize(kSize), src(src) {
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
        imshow("My Window", dst);
    } else {
        dst = src->clone();
        imshow("My Window", dst);

    }
}


void GaussianBlurData::MyCallbackForGaussianBlurSigma(int sigmaTrackbar, void *userData) {
    auto data = *(static_cast<GaussianBlurData *>(userData));

    data.redraw();
}

void GaussianBlurData::MyCallbackForGaussianBlurKSizeXY(int kSizeXY, void *userData) {
    auto data = *(static_cast<GaussianBlurData *>(userData));

    data.redraw();
}

