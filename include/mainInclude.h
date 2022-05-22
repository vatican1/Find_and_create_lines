#ifndef FIND_AND_CREATE_LINES_MAININCLUDE_H
#define FIND_AND_CREATE_LINES_MAININCLUDE_H

#include "TrackbarsData.h"

struct AllTransforms {
    cv::Mat src_;
    GaussianBlurData gaussianBlurData;

    AllTransforms(cv::Mat &src) : gaussianBlurData(GaussianBlurData(15, 40, &src, "Blur")), src_(src) {
        namedWindow("Blur", cv::WINDOW_NORMAL);
    }

    void redraw() {
        gaussianBlurData.redraw();
    }
};

#endif
