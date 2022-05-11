#include "./Tests.h"
#include "./RemovingExtraLines.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "TrackbarsData.h"

void testIntersectionPoint() {
    cv::Mat src(600, 600, CV_8UC1, cv::Scalar(255, 255, 255));
    cv::Vec4i v1(1, 1, 200, 200);
    cv::Vec4i v2(1, 599, 200, 399);
    std::vector<cv::Vec4i> vect;
    vect.push_back(v1);
    vect.push_back(v2);

    std::pair point_b = findIntersectionPoint(v1, v2);
    if (point_b.second == false)
        return;
    cv::Point point = point_b.first;

    cv::circle(src,point,4, cv::Scalar(0,0,255),-1);
    for (size_t i = 0; i < vect.size(); i++) {
        cv::Vec4i l = vect[i];
        cv::line(src, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    }
    cv::namedWindow("testIntersectionDot", cv::WINDOW_AUTOSIZE);
    imshow("testIntersectionDot", src);

    cv::waitKey(0);
}


