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
    cv::Point point;
    cv::Point proposed_center = cv::Point(0, 0);
    int k = 0;


    AllTransforms(cv::Mat &src) : src_(src) {


        gaussianBlurData = GaussianBlurData(1, 5, &src_, "Blur");

        cv::createTrackbar("Gaussian blur sigma", gaussianBlurData.winName, &gaussianBlurData.sigma, 100,
                           GaussianBlurData::MyCallbackForGaussianBlurSigma, this);

        cv::createTrackbar("Gaussian blur kSize", gaussianBlurData.winName, &gaussianBlurData.kSize, 60,
                           GaussianBlurData::MyCallbackForGaussianBlurKSizeXY, this);
//        gaussianBlurData.redraw();

//        EdgeDetector::LaplacianData operatorData2 = {3};
//        EdgeDetector::CannyData operatorData3 = {10, 100, 3, false};
        EdgeDetector::SobelData operatorData1 = {1, 0, 3};
        edgeDetector = EdgeDetector(&gaussianBlurData.dst, EdgeDetector::Operators::SOBEL, operatorData1);
        edgeDetector.applyEdgeDetectOperator();
//        cv::imwrite("data_mod/SobelxSPB2.JPEG", edgeDetector.dst);


//        cv::Mat some;
//        cv::cvtColor(edgeDetector.dst, some, cv::COLOR_GRAY2BGR);
//        EdgeDetector edgeDetector2 = EdgeDetector(&some, EdgeDetector::Operators::SOBEL, operatorData1);
//        edgeDetector2.applyAndFirstDraw();
//        cv::imwrite("data_mod/Sobelx2.JPEG", edgeDetector2.dst);
//
        houghLines = HoughLines(&edgeDetector.dst, "houghT", proposed_center);
        std::pair<cv::Point, int> pair = houghLines.CreateHoughLines(src_);
        point = pair.first;
        int num1 = pair.second;
        std::cout << num1 << std::endl;
        int num = num1;
        gaussianBlurData.sigma = 400;

        while (!(num > num1 / 20 - num1 / 100 && num < num1 / 20 + num1 / 100)) {
            gaussianBlurData.sigma -= 3;
            std::cout << gaussianBlurData.sigma << std::endl;
            gaussianBlurData.redo();
            edgeDetector.applyEdgeDetectOperator();
            pair = houghLines.CreateHoughLines(src_);
            num = pair.second;
        }
//        houghLines.redraw();
//        cv::imwrite("data_mod/HoughSPB_" + std::to_string(k) + ".JPG", houghLines.dst);


        init = true;

    }

    void redraw() {
        if (init) {
            gaussianBlurData.redraw();
            edgeDetector.applyEdgeDetectOperator();
            edgeDetector.redraw();
            std::pair<cv::Point, int> pair = houghLines.CreateHoughLines(src_);
            point = pair.first;
            houghLines.redraw();
            cv::imwrite("data_mod/HoughSPB_" + std::to_string(k) + ".JPG", houghLines.dst);
            k++;
        }

    }
};

#endif
