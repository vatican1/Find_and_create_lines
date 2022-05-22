#ifndef FIND_AND_CREATE_LINES_ALLFILTERS_H
#define FIND_AND_CREATE_LINES_ALLFILTERS_H

#include "TrackbarsData.h"
#include "EdgeDetector.h"

struct AllTransforms {
    cv::Mat src_;
    GaussianBlurData gaussianBlurData;
    EdgeDetector edgeDetector;

    explicit AllTransforms(cv::Mat &src) : src_(src) {
        gaussianBlurData = GaussianBlurData(15, 40, &src, "Blur");
        edgeDetector = EdgeDetector(&gaussianBlurData.dst);
        namedWindow("Blur", cv::WINDOW_NORMAL);
    }

    void redraw() {
        gaussianBlurData.redraw();

        EdgeDetector::SobelData operatorData1 = {1, 0, 3};
//    LaplacianData operatorData2 = {3};
//    CannyData operatorData3 = {10, 100, 3, false};
        edgeDetector.applyEdgeDetectOperator(EdgeDetector::Operators::SOBEL, &operatorData1);
        edgeDetector.redraw();

    }
};

#endif
