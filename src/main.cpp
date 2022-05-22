#include <iostream>
#include <string>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "TrackbarsData.h"

#include "./Tests.h"
#include "./RemovingExtraLines.h"
#include "mainInclude.h"


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




int main() {
    std::string picturesNames[] = {"Helsinki_1.JPEG", "Helsinki_2.JPEG", "Saint-Petersburg_1.JPEG",
                                   "Saint-Petersburg_2.JPEG", "Saint-Petersburg_3.JPEG", "Tbilisi_1.JPEG"};
    cv::Mat src = cv::imread("data/" + picturesNames[0]);
    if (src.empty()) {
        std::cout << "Error loading src1" << std::endl;
        return -1;
    }


    AllTransforms a(src);

    cv::createTrackbar("Gaussian blur sigma", a.gaussianBlurData.winName, &a.gaussianBlurData.sigma, 100,
                       GaussianBlurData::MyCallbackForGaussianBlurSigma, &a);
    cv::createTrackbar("Gaussian blur kSize", a.gaussianBlurData.winName, &a.gaussianBlurData.kSize, 60,
                       GaussianBlurData::MyCallbackForGaussianBlurKSizeXY, &a);


//    SobelData operatorData1 = {1, 0, 3};
//    applyEdgeDetectOperator(data->dst, dst, Operators::SOBEL, &operatorData1);


//    LaplacianData operatorData2 = {3};
//    applyEdgeDetectOperator(data->dst, Operators::LAPLACIAN, &operatorData2);
//
//    CannyData operatorData3 = {10, 100, 3, false};
//    applyEdgeDetectOperator(data->dst, Operators::CANNY, &operatorData3);

    cv::waitKey(0);


    return 0;
}



