
#include "opencv2/opencv.hpp"
#include "BlureData.h"
#include "AllFilters.h"


GaussianBlurData::GaussianBlurData(int sigma, int kSize, cv::Mat *src, std::string winName) : sigma(sigma),
                                                                                              kSize(kSize), src(src),
                                                                                              winName(winName) {
    dst = src->clone();
    namedWindow(winName, cv::WINDOW_NORMAL);
}

cv::Size GaussianBlurData::getKSize() {
    return cv::Size{2 * kSize + 1, 2 * kSize + 1};
}

double GaussianBlurData::getSigma() {
    return (double) sigma / 80;
}

void GaussianBlurData::redraw() {
    if (sigma != 0 && kSize != 0) {
        cv::GaussianBlur(*src, dst, this->getKSize(), this->getSigma());
        imshow(winName, dst);
    } else {
        dst = src->clone();
        imshow(winName, dst);
    }
}

void GaussianBlurData::redo() {
        cv::GaussianBlur(*src, dst, this->getKSize(), this->getSigma());

}


void GaussianBlurData::MyCallbackForGaussianBlurSigma(int sigmaTrackbar, void *userData) {
    reinterpret_cast<AllTransforms *>(userData)->redraw();
}

void GaussianBlurData::MyCallbackForGaussianBlurKSizeXY(int kSizeXY, void *userData) {
    reinterpret_cast<AllTransforms *>(userData)->redraw();
}

GaussianBlurData::GaussianBlurData() {}



