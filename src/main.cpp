#include <iostream>
#include <string>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "TrackbarsData.h"

#include "./Tests.h"
#include "./RemovingExtraLines.h"


void HoughLinesDraw(const cv::Mat &grad, const std::string &windowName) {
    cv::Mat dst, cdst;

    Canny(grad, dst, 50, 200, 3);
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);
    cv::Mat cdstP = cdst.clone();

    // Probabilistic Line Transform
    std::vector<cv::Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection

    cv::Point point1 = deleteExtraLines(linesP);
    int cirlceSize = std::min(grad.size().height, grad.size().width) / 10;
    cv::circle(dst, point1, cirlceSize, cv::Scalar(0, 0, 0), -1);

    std::vector<cv::Vec4i> linesP2;
    HoughLinesP(dst, linesP2, 1, CV_PI / 180, 50, 50, 10);
    cv::Point point2 = deleteExtraLines(linesP2);
    cv::circle(cdstP, point1, 5, cv::Scalar(255, 0, 0), -1);

    // Рисуем линии
    for (auto l: linesP2) {
        line(cdstP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    }

    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    imshow(windowName, cdstP);
}

enum class Operators {
    SOBEL,
    LAPLACIAN,
    CANNY
};

struct SobelData {
    int dx; // порядок производной
    int dy;
    int ksize; // размер матрицы оператора - только 1, 3, 5, 7
//    double scale; // коэффициент масштабирования для вычисления производной.
//    double delta; //  прибавляется к итоговому значению
};

struct LaplacianData {
    int ksize; //
};

struct CannyData {
    double threshold1;
    double threshold2;
    int apertureSize;
    bool L2gradient;
};

cv::Mat applyEdgeDetectOperator(const cv::Mat &src, Operators op, void *data) {
    cv::Mat srcBlurGray;
    cv::cvtColor(src, srcBlurGray, cv::COLOR_BGR2GRAY);


    std::string windowName;
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

    cv::Mat abs_grad;
    cv::convertScaleAbs(grad, abs_grad);
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::imshow(windowName, abs_grad);
    return abs_grad;
}


int main() {
    std::string picturesNames[] = {"Helsinki_1.JPEG", "Helsinki_2.JPEG", "Saint-Petersburg_1.JPEG",
                                   "Saint-Petersburg_2.JPEG", "Saint-Petersburg_3.JPEG", "Tbilisi_1.JPEG"};
    cv::Mat src = cv::imread("data/" + picturesNames[0]);
    if (src.empty()) {
        std::cout << "Error loading src1" << std::endl;
        return -1;
    }


    namedWindow("My Window", cv::WINDOW_NORMAL);
    auto *data = new GaussianBlurData(15, 40, &src);
    cv::createTrackbar("Gaussian blur sigma", "My Window", &data->sigma, 100,
                       GaussianBlurData::MyCallbackForGaussianBlurSigma, data);
    cv::createTrackbar("Gaussian blur kSize", "My Window", &data->kSize, 60,
                       GaussianBlurData::MyCallbackForGaussianBlurKSizeXY, data);


    cv::Mat srcBlurGray1;
    while (true) {
        SobelData operatorData1 = {1, 0, 3};
        applyEdgeDetectOperator(data->dst, Operators::SOBEL, &operatorData1);

        LaplacianData operatorData2 = {3};
        applyEdgeDetectOperator(data->dst, Operators::LAPLACIAN, &operatorData2);

        CannyData operatorData3 = {10, 100, 3, false};
        applyEdgeDetectOperator(data->dst, Operators::CANNY, &operatorData3);
        cv::waitKey(0);
    }

    return 0;
}



