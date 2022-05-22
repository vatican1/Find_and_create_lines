#include <iostream>
#include "HoughTransform.h"


void HoughLines::redraw() {
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    imshow(windowName, dst);
}

void HoughLines::CreateHoughLines() {
    cv::Mat tmp = src->clone();

    std::vector<cv::Vec4i> linesP;
    HoughLinesP(tmp, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection

    cv::Point point1 = deleteExtraLines(linesP);
//    std::cout<<"!!"<<std::endl;
//    int cirlceSize = std::min(src->size().height, src->size().width) / 10;
//    cv::circle(tmp, point1, cirlceSize, cv::Scalar(0, 0, 0), -1);
//
//    std::vector<cv::Vec4i> linesP2;
//    HoughLinesP(tmp, linesP2, 1, CV_PI / 180, 50, 50, 10);
//    cv::Point point2 = deleteExtraLines(linesP2);
    cv::circle(dst, point1, 5, cv::Scalar(255, 0, 0), -1);

    for (auto l: linesP) {
        line(dst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    }

}

HoughLines::HoughLines(cv::Mat *src, std::string windowName) : src(src), windowName(windowName) {

}

HoughLines::HoughLines() {

}
