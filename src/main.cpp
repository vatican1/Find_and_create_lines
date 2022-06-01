#include <iostream>
#include <string>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "BlureData.h"

#include "Tests.h"
#include "AllFilters.h"

#define dp0x data->points[0].x
#define dp1x data->points[1].x
#define dp2x data->points[2].x
#define dp3x data->points[3].x

struct AboutDraw {
    cv::Mat *src;
    cv::Mat *tmp;
    cv::Point main_point;
    bool bp1;
    bool bp2;
    bool bp3;
    cv::Point points[4];
};

void Fillquadrangle(cv::Point points[4], cv::Mat *src, cv::Vec3b v) {
    for (int x = 0; x < src->size().width; x++)
        for (int y = std::min(points[0].y, points[2].y);
             y < std::max(points[0].y, points[2].y); y++)
            if (x > points[0].x + (points[0].x - points[2].x) * (y - points[0].y) /
                                  (points[0].y - points[2].y)
                && x < points[1].x + (points[1].x - points[3].x) * (y - points[1].y) /
                                     (points[1].y - points[3].y))
                src->at<cv::Vec3b>(y, x) = v;
}


void MouseCallBackPaint(int event, int x, int y, int flags, void *userdata) {
    auto *data = (AboutDraw *) userdata;

    if (event == cv::EVENT_LBUTTONDOWN) {

        if (data->bp1 || data->bp2 || data->bp3) {
            cv::circle(*data->tmp, cv::Point(x, y), 5, cv::Scalar(255, 0, 0), -1);
        }
        if (data->bp3) {
            data->bp3 = false;
            *data->tmp = data->src->clone();
            int x_new[2];
            cv::Point points[2] = {data->points[0], data->points[1]};
            for (int i = 0; i < 2; i++) {
                int k = 1;
                if (points[i].x > data->main_point.x)
                    k = -1;

                x_new[i] = points[i].x + k * abs(points[i].x - data->main_point.x) * abs(y - points[i].y) /
                                         abs(data->main_point.y - points[i].y);
            }
            data->points[2] = cv::Point(x_new[0], y);
            data->points[3] = cv::Point(x_new[1], y);
            data->points[0].y = std::max(data->points[0].y, data->points[1].y);
            data->points[1].y = std::max(data->points[0].y, data->points[1].y);

            cv::line(*data->tmp, data->points[0], data->points[2], cv::Scalar(30, 30, 255), 1, cv::LINE_AA);
            cv::line(*data->tmp, data->points[1], data->points[3], cv::Scalar(30, 30, 255), 1, cv::LINE_AA);
            Fillquadrangle(data->points, data->tmp, cv::Vec3b(30, 30, 255));

            int amount = 20;
            int _1_width = 10;
            int _1_height = 10;

            for (int i = 1; i < amount + 1; i += 2) {
                cv::Point new_points[4];
                int stepy = abs(data->points[0].y - data->points[2].y) / amount;

                int xLnow = dp0x + (dp2x - dp0x) / amount * i;
                int xRnow = dp1x - (dp1x - dp3x) / amount * i;
                int betweenx = abs(xLnow - xRnow);

                int xLnext = dp0x + (dp2x - dp0x) / amount * (i + 1);
                int xRnext = dp1x - (dp1x - dp3x) / amount * (i + 1);
                int betweenxNext = abs(xLnext - xRnext);

                int indentxnow = betweenx * (_1_width - 1) / (2 * _1_width);
                int identxNext = betweenxNext * (_1_width - 1) / (2 * _1_width);

                new_points[0] = cv::Point(xLnow + indentxnow, data->points[0].y - i * stepy);
                new_points[2] = cv::Point(xLnext + identxNext, data->points[0].y - (i + 1) * stepy);

                new_points[1] = cv::Point(xRnow - indentxnow, data->points[0].y - i * stepy);
                new_points[3] = cv::Point(xRnext - identxNext, data->points[0].y - (i + 1) * stepy);

                Fillquadrangle(new_points, data->tmp, cv::Vec3b(200, 200, 200));

            }
        }
        if (data->bp2) {
            data->points[1] = cv::Point(x, y);
            data->bp2 = false;
            data->bp3 = true;
            cv::line(*data->tmp, data->points[1], data->main_point, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        }
        if (data->bp1) {
            data->points[0] = cv::Point(x, y);
            data->bp1 = false;
            data->bp2 = true;
            cv::line(*data->tmp, data->points[0], data->main_point, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
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
    cv::setMouseCallback("Paint", MouseCallBackPaint, &d);
    cv::waitKey(0);

    return 0;
}



