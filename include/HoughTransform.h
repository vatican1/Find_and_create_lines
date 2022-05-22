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

    HoughLines(cv::Mat *src, std::string windowName);

    HoughLines();

    void CreateHoughLines();

    void redraw();
};

#endif //FIND_AND_CREATE_LINES_HOUGHTRANSFORM_H
