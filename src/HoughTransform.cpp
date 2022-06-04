#include <iostream>
#include "HoughTransform.h"


void HoughLines::redraw() {
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    imshow(windowName, dst);
}

std::pair<cv::Point, int> HoughLines::CreateHoughLines(cv::Mat &ImgWhereDraw) {
    cv::Mat tmp = src->clone();
    cv::Mat tmp2 = src->clone();
    std::vector<cv::Vec4i> linesP;
    cv::Canny(*src, tmp, 50, 200, 3);
    cv::cvtColor(tmp, tmp2, cv::COLOR_GRAY2BGR);
    HoughLinesP(tmp, linesP, 1, CV_PI / 180, 80, 100, 10); // runs the actual detection
    int num = linesP.size();
    if (!linesP.empty()) {
        cv::Point point1 = deleteExtraLines(linesP, this->centrePoint);
        int cirlceSize = std::min(src->size().height, src->size().width) / 10;
        cv::circle(tmp, point1, cirlceSize, cv::Scalar(0, 0, 0), -1);
    }

    cv::Point point_r = cv::Point(src->size().width / 2, src->size().height / 2);
    std::vector<cv::Vec4i> linesP2;
    HoughLinesP(tmp, linesP2, 1, CV_PI / 180, 80, 120, 10);
    if (!linesP2.empty()) {
        cv::Point point2 = deleteExtraLines(linesP2, this->centrePoint);
        for (auto l: linesP) {
            cv::line(tmp2, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        }
        cv::circle(tmp2, point2, 5, cv::Scalar(255, 0, 0), -1);
        point_r = point2;
    }


//    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
//    imshow(windowName, tmp2);
    dst = tmp2.clone();
    return std::make_pair(point_r, num);

}

HoughLines::HoughLines(cv::Mat *src, std::string windowName, cv::Point point) : src(src), windowName(windowName),
                                                                                dst(*src), centrePoint(point) {

}

HoughLines::HoughLines() {

}
