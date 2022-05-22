#include "EdgeDetector.h"
#include "AllFilters.h"

cv::Mat EdgeDetector::applyEdgeDetectOperator() {
    cv::Mat srcBlurGray;
    cv::cvtColor(*src, srcBlurGray, cv::COLOR_BGR2GRAY);

    cv::Mat grad;
    switch (op) {
        case Operators::SOBEL: {
            windowName = "Sobel dx = " + std::to_string(sobelData.dx) + " dy = " + std::to_string(sobelData.dy) +
                         " ksize = " + std::to_string(sobelData.ksize);
            cv::Sobel(srcBlurGray, grad, CV_16S, sobelData.dx, sobelData.dy, sobelData.ksize);
            break;
        }
        case Operators::LAPLACIAN: {
            windowName = "Laplacian ksize = " + std::to_string(laplacianData.ksize);
            cv::Laplacian(srcBlurGray, grad, CV_16S, laplacianData.ksize);
            break;
        }
        case Operators::CANNY: {
            windowName = "Canny threshold1 = " + std::to_string(cannyData.threshold1) +
                         " threshold2 = " + std::to_string(cannyData.threshold2) + " apertureSize = " +
                         std::to_string(cannyData.apertureSize) + " L2gradient = " +
                         std::to_string(cannyData.L2gradient);
            cv::Canny(srcBlurGray, grad, cannyData.threshold1, cannyData.threshold2, cannyData.apertureSize,
                      cannyData.L2gradient);
            break;
        }
    }

    cv::convertScaleAbs(grad, dst);
    return dst;
}


void EdgeDetector::redraw() {
    cv::imshow(windowName, dst);
}

EdgeDetector::EdgeDetector() {}

EdgeDetector::EdgeDetector(cv::Mat *src, EdgeDetector::Operators op,
                           EdgeDetector::SobelData sobel) :
        src(src), op(op), sobelData(sobel) {
}

EdgeDetector::EdgeDetector(cv::Mat *src, EdgeDetector::Operators op,
                           EdgeDetector::LaplacianData laplacian) :
        src(src), op(op), laplacianData(laplacian) {
}

EdgeDetector::EdgeDetector(cv::Mat *src, EdgeDetector::Operators op,
                           EdgeDetector::CannyData canny) :
        src(src), op(op), cannyData(canny) {
}

void EdgeDetector::applyAndFirstDraw() {
    std::cout << "apply and detect first" << std::endl;
    applyEdgeDetectOperator();
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    redraw();
}











