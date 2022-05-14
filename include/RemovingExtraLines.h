# pragma once

#include <opencv2/core/types.hpp>

std::pair<cv::Point, bool> findIntersectionPoint(const cv::Vec4i &v1, const cv::Vec4i &v2);

//Кидает false, если линии почти параллельны.
cv::Point fingIntersectPointOfAllLines(const std::vector<cv::Vec4i> &lines);

float distanceBetweenPointAndLine(const cv::Point& point, const cv::Vec4i& line);

cv::Point deleteExtraLines(std::vector<cv::Vec4i> &lines);