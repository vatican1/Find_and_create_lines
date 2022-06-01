#include <iostream>
#include <string>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "BlureData.h"

#include "Tests.h"
#include "AllFilters.h"

struct AboutDraw {
    cv::Mat *src;
    cv::Mat *tmp;
    cv::Point main_point;
    bool bp1;
    bool bp2;
    bool bp3;
    cv::Point p1;
    cv::Point p2;
    cv::Point p3;
};


void MouseCallBack(int event, int x, int y, int flags, void *userdata) {
    auto *data = (AboutDraw *) userdata;

//    if ((flags & cv::EVENT_FLAG_LBUTTON) && event == cv::EVENT_MOUSEMOVE) {
//        cv::line(*p->tmp, cv::Point(x, y), *p->main_point, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
//        cv::imshow("Paint", *p->tmp);
//        *p->tmp = p->src->clone();
//
//        cv::imshow("paint", *p->src);
//    }

    if (event == cv::EVENT_LBUTTONDOWN) {

        if (data->bp1 || data->bp2 || data->bp3) {
            cv::circle(*data->tmp, cv::Point(x, y), 5, cv::Scalar(255, 0, 0), -1);
        }
        if (data->bp3) {
            data->p3 = cv::Point(x, y);
            data->bp3 = false;
            *data->tmp = data->src->clone();
            int x_new[2];
            cv::Point points[2] = {data->p1, data->p2};
            for (int i = 0; i < 2; i++) {
                int k = 1;
                if (points[i].x > data->main_point.x)
                    k = -1;

                x_new[i] = points[i].x + k * abs(points[i].x - data->main_point.x) * abs(y - points[i].y) /
                                         abs(data->main_point.y - points[i].y);
            }


            cv::line(*data->tmp, data->p1, cv::Point(x_new[0], y), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
            cv::line(*data->tmp, data->p2, cv::Point(x_new[1], y), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        }
        if (data->bp2) {
            data->p2 = cv::Point(x, y);
            data->bp2 = false;
            data->bp3 = true;
            cv::line(*data->tmp, data->p2, data->main_point, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        }
        if (data->bp1) {
            data->p1 = cv::Point(x, y);
            data->bp1 = false;
            data->bp2 = true;
            cv::line(*data->tmp, data->p1, data->main_point, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        }
        cv::imshow("Paint", *data->tmp);

    }


}


int main() {
    std::string picturesNames[] = {"Helsinki_1.JPEG", "Helsinki_2.JPEG", "Saint-Petersburg_1.JPEG",
                                   "Saint-Petersburg_2.JPEG", "Saint-Petersburg_3.JPEG", "Tbilisi_1.JPEG"};
    cv::Mat src = cv::imread("data/" + picturesNames[0]);
    if (src.empty()) {
        std::cout << "Error loading src1" << std::endl;
        return -1;
    }

    AllTransforms a(src);
    cv::Point p = a.point;
    cv::waitKey(0);
    cv::namedWindow("Paint", cv::WINDOW_NORMAL);
    imshow("Paint", src);
    cv::Mat tmp = src.clone();
    AboutDraw d = {&src, &tmp, p, true, false, false};
    cv::setMouseCallback("Paint", MouseCallBack, &d);
    cv::waitKey(0);

    return 0;
}



