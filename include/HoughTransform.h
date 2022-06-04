#ifndef FIND_AND_CREATE_LINES_HOUGHTRANSFORM_H
#define FIND_AND_CREATE_LINES_HOUGHTRANSFORM_H

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "RemovingExtraLines.h"

struct HoughLines {
    std::string windowName;
    cv::Mat *src;
    cv::Mat dst;
    cv::Point centrePoint;

    HoughLines(cv::Mat *src, std::string windowName, cv::Point centrePoint);

    HoughLines();

    std::pair<cv::Point, int> CreateHoughLines(cv::Mat &ImgWhereDraw);

    void redraw();
};

#endif //FIND_AND_CREATE_LINES_HOUGHTRANSFORM_H
