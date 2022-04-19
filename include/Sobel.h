#ifndef FIND_AND_CREATE_LINES_SOBEL_H
#define FIND_AND_CREATE_LINES_SOBEL_H

#include "opencv2/opencv.hpp"
#include "opencv2/opencv.hpp"

class SobelData{
public:
    cv::Mat* src;
    cv::Mat dst;

};

void MyCallbackForGrad_(int, void* data);

#endif
//src_gray: In our example, the input image. Here it is CV_8U
//grad_x / grad_y : The output image.
//ddepth: The depth of the output image. We set it to CV_16S to avoid overflow.
//x_order: The order of the derivative in x direction.
//y_order: The order of the derivative in y direction.
//scale, delta and BORDER_DEFAULT: We use default values.

