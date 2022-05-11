#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "TrackbarsData.h"

#include "./Tests.h"
#include "./RemovingExtraLines.h"



void redraw(const cv::Mat &grad, const char windowName[]) {
    cv::Mat dst, cdst, cdstP;

    Canny(grad, dst, 50, 200, 3);
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);
    cdstP = cdst.clone();
    cv::Mat cdstP2 = cdst.clone();

    // Probabilistic Line Transform
    std::vector<cv::Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection


    // Рисование линий
    for (size_t i = 0; i < linesP.size(); i++) {
        cv::Vec4i l = linesP[i];
        line(cdstP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    }
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);

    imshow(windowName, cdstP);

    deleteExtraLines(linesP);

    for (size_t i = 0; i < linesP.size(); i++) {
        cv::Vec4i l = linesP[i];
        line(cdstP2, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    }

    cv::namedWindow("delete", cv::WINDOW_NORMAL);

    imshow("delete", cdstP2);
}

int main() {
    cv::Mat src = cv::imread("data/Helsinki_1.JPEG");
    if (src.empty()) {
        std::cout << "Error loading src1 \n";
        return -1;
    }


    namedWindow("My Window", cv::WINDOW_NORMAL);
    auto *data = new GaussianBlurData(0, 1, &src);
    cv::createTrackbar("Gaussian blur sigma", "My Window", &data->sigma, 100,
                       GaussianBlurData::MyCallbackForGaussianBlurSigma, data);
    cv::createTrackbar("Gaussian blur kSize", "My Window", &data->kSize, 10,
                       GaussianBlurData::MyCallbackForGaussianBlurKSizeXY, data);

    cv::Mat srcBlurGray1;
    while (true) {
        cv::cvtColor(data->dst, srcBlurGray1, cv::COLOR_BGR2GRAY);

        cv::Mat grad;

        cv::Mat grad_x, grad_y;
        cv::Mat abs_grad_x, abs_grad_y;

        cv::Sobel(srcBlurGray1, grad_x, CV_16S, 1, 0);
        cv::Sobel(srcBlurGray1, grad_y, CV_16S, 0, 1);

        convertScaleAbs(grad_x, abs_grad_x);// пойми что это
        convertScaleAbs(grad_y, abs_grad_y);// пойми что это
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);// тут логично рисуется картинка с общим градиентом.


        redraw(grad, "grad");
       // redraw(abs_grad_x, "abs_grad_x");
        //redraw(abs_grad_y, "abs_grad_y");

        cv::waitKey(0);
    }

    return 0;
}



