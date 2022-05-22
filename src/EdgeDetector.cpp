#include "EdgeDetector.h"
#include "AllFilters.h"

cv::Mat EdgeDetector::applyEdgeDetectOperator(Operators op, void *data) {
    cv::Mat srcBlurGray;
    cv::cvtColor(*src, srcBlurGray, cv::COLOR_BGR2GRAY);


    cv::Mat grad;
    switch (op) {
        case Operators::SOBEL: {
            auto *castData = static_cast<SobelData *>(data);
            windowName = "Sobel dx = " + std::to_string(castData->dx) + " dy = " + std::to_string(castData->dy) +
                         " ksize = " + std::to_string(castData->ksize);
            cv::Sobel(srcBlurGray, grad, CV_16S, castData->dx, castData->dy, castData->ksize);
            break;
        }
        case Operators::LAPLACIAN: {
            auto *castData = static_cast<LaplacianData *>(data);
            windowName = "Laplacian ksize = " + std::to_string(castData->ksize);
            cv::Laplacian(srcBlurGray, grad, CV_16S, castData->ksize);
            break;
        }
        case Operators::CANNY: {
            auto *castData = static_cast<CannyData *>(data);
            windowName = "Canny threshold1 = " + std::to_string(castData->threshold1) +
                         " threshold2 = " + std::to_string(castData->threshold2) + " apertureSize = " +
                         std::to_string(castData->apertureSize) + " L2gradient = " +
                         std::to_string(castData->L2gradient);
            cv::Canny(srcBlurGray, grad, castData->threshold1, castData->threshold2, castData->apertureSize,
                      castData->L2gradient);
            break;
        }
    }

    cv::convertScaleAbs(grad, dst);
    return dst;
}

EdgeDetector::EdgeDetector(cv::Mat *src) : src(src) {
    cv::namedWindow("SOME", cv::WINDOW_NORMAL);
}

void EdgeDetector::redraw() {
    cv::imshow("SOME", dst);
}

EdgeDetector::EdgeDetector() {

}


