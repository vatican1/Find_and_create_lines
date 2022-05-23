#include <iostream>
#include "HoughTransform.h"


//void HoughLines::redraw() {
//    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
//    imshow(windowName, dst);
//}

void HoughLines::CreateHoughLines(cv::Mat &ImgWhereDraw) {
    cv::Mat tmp = src->clone();
    cv::Mat tmp2 = src->clone();
    std::vector<cv::Vec4i> linesP;
    cv::Canny(*src, tmp, 50, 200, 3);
    cv::cvtColor(tmp, tmp2,cv::COLOR_GRAY2BGR);
    HoughLinesP(tmp, linesP, 1, CV_PI / 180, 80, 100, 10); // runs the actual detection

    if (!linesP.empty()) {
        cv::Point point1 = deleteExtraLines(linesP);
        int cirlceSize = std::min(src->size().height, src->size().width) / 10;
        cv::circle(tmp, point1, cirlceSize, cv::Scalar(0, 0, 0), -1);
    }

    std::vector<cv::Vec4i> linesP2;
    HoughLinesP(tmp, linesP2, 1, CV_PI / 180, 80, 120, 10);
    if (!linesP2.empty()) {
        cv::Point point2 = deleteExtraLines(linesP2);
        for (auto l: linesP) {
            line(tmp2, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        }
        cv::circle(tmp2, point2, 5, cv::Scalar(255, 0, 0), -1);
    }


    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    imshow(windowName, tmp2);

}

HoughLines::HoughLines(cv::Mat *src, std::string windowName) : src(src), windowName(windowName), dst(*src) {

}

HoughLines::HoughLines() {

}
