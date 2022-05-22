#ifndef FIND_AND_CREATE_LINES_ALLFILTERS_H
#define FIND_AND_CREATE_LINES_ALLFILTERS_H

#include "BlureData.h"
#include "EdgeDetector.h"
#include "HoughTransform.h"

struct AllTransforms {
    cv::Mat src_;
    GaussianBlurData gaussianBlurData;
    EdgeDetector edgeDetector;
    HoughLines houghLines;
    bool init = false;

    AllTransforms(cv::Mat &src) : src_(src) {


        gaussianBlurData = GaussianBlurData(15, 40, &src_, "Blur");

        cv::createTrackbar("Gaussian blur sigma", gaussianBlurData.winName, &gaussianBlurData.sigma, 100,
                           GaussianBlurData::MyCallbackForGaussianBlurSigma, this);

        cv::createTrackbar("Gaussian blur kSize", gaussianBlurData.winName, &gaussianBlurData.kSize, 60,
                           GaussianBlurData::MyCallbackForGaussianBlurKSizeXY, this);

//        EdgeDetector::LaplacianData operatorData2 = {3};
//        EdgeDetector::CannyData operatorData3 = {10, 100, 3, false};
        EdgeDetector::SobelData operatorData1 = {1, 0, 3};
        edgeDetector = EdgeDetector(&gaussianBlurData.dst, EdgeDetector::Operators::SOBEL, operatorData1);
        edgeDetector.applyAndFirstDraw();

        houghLines = HoughLines(&edgeDetector.dst, "houghT");


        init = true;

    }

    void redraw() {
        if (init) {
            gaussianBlurData.redraw();
            edgeDetector.applyEdgeDetectOperator();
            edgeDetector.redraw();
            houghLines.CreateHoughLines();
//            houghLines.redraw();
        }

    }
};

#endif
