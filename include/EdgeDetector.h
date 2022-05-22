#ifndef FIND_AND_CREATE_LINES_EDGEDETECTOR_H
#define FIND_AND_CREATE_LINES_EDGEDETECTOR_H

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

struct EdgeDetector {

    cv::Mat *src;
    cv::Mat dst;
    std::string windowName;

    enum class Operators {
        SOBEL,
        LAPLACIAN,
        CANNY
    } op;

    struct SobelData {
        int dx; // порядок производной
        int dy;
        int ksize; // размер матрицы оператора - только 1, 3, 5, 7
//    double scale; // коэффициент масштабирования для вычисления производной.
//    double delta; //  прибавляется к итоговому значению
    } sobelData;

    struct LaplacianData {
        int ksize; //
    } laplacianData;

    struct CannyData {
        double threshold1;
        double threshold2;
        int apertureSize;
        bool L2gradient;
    } cannyData;

    EdgeDetector();

    EdgeDetector(cv::Mat *src, Operators op, SobelData sobel);

    EdgeDetector(cv::Mat *src, Operators op, LaplacianData laplacian);

    EdgeDetector(cv::Mat *src, Operators op, CannyData canny);


    void applyAndFirstDraw();

    cv::Mat applyEdgeDetectOperator();

    void redraw();


};

#endif //FIND_AND_CREATE_LINES_EDGEDETECTOR_H
