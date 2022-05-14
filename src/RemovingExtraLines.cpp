#include <utility>
#include <opencv2/core/matx.hpp>

#include <map>
#include <iostream>

# include "./RemovingExtraLines.h"

std::pair<cv::Point, bool> findIntersectionPoint(const cv::Vec4i &line1, const cv::Vec4i &line2) {
    float x1 = line1[0];
    float y1 = line1[1];
    float x2 = line1[2];
    float y2 = line1[3];

    float x3 = line2[0];
    float y3 = line2[1];
    float x4 = line2[2];
    float y4 = line2[3];

    if ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4) < 0.1)
        std::make_pair(cv::Point(0, 0), false);

    float px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
               ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    float py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
               ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    return std::make_pair(cv::Point(px, py), true);
}


cv::Point fingIntersectPointOfAllLines(std::vector<cv::Vec4i> &lines) {
    //  создали массив точек, подозрительных на точку пересечения линий перспективы
    std::map<std::pair<int, int>, int> pointMap;
    //всё кроме этого работает бывстро, надо успростить!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for (int i = 0; i < lines.size(); i += 3) {
        for (int j = i; j < lines.size(); j += 3) {
            float x1 = lines[i][0];
            float y1 = lines[i][1];
            float x2 = lines[i][2];
            float y2 = lines[i][3];

            float x3 = lines[j][0];
            float y3 = lines[j][1];
            float x4 = lines[j][2];
            float y4 = lines[j][3];

            if ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4) < 0.1)
                continue;

            float px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
                       ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
            float py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
                       ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

            if (pointMap.find(std::make_pair(px, py)) == pointMap.end())
                pointMap[std::make_pair(px, py)] = 1;
            else
                pointMap[std::make_pair(px, py)]++;
        }
    }

    // Возможно стоит проредить точки, расположенные рядом, пока не будем
    // найдём самую лучшую точку(потом можно добавить найти среднее арифметическое самых часто встречающихся или реализовать, что придумано до этого)
    // проредить выгодно с точки зрения производительности, но голосование выгоднее с точки зрения точности, подумай что лучше
    cv::Point bestPoint;
    int vote = 0;
    for (auto i: pointMap) {
        if (i.second > vote) {
            vote = i.second;
            bestPoint = cv::Point(i.first.first, i.first.second);
        }
    }
    return bestPoint;
}

float inline distanceBetweenPointAndLine(const cv::Point &point, const cv::Vec4i &line) {
    float x1 = line[0];
    float y1 = line[1];
    float x2 = line[2];
    float y2 = line[3];
    float x0 = point.x;
    float y0 = point.y;

    float d = abs((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1);
    d /= (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1);
    return d;
}

cv::Point deleteExtraLines(std::vector<cv::Vec4i> &lines) {

    cv::Point bestPoint = fingIntersectPointOfAllLines(lines);
    int linesSize = lines.size();
    // сначала надо найти среднее отклонение, потом удалить прямые, которые не сильно к нему подходят
    int sum = 0;
    for (auto line: lines) {
        sum += distanceBetweenPointAndLine(bestPoint, line);
    }
    float avg = sum / lines.size();

    int deleted = 0;
    for (auto it = lines.begin(); it != lines.end();) {
        if (distanceBetweenPointAndLine(bestPoint, *it) > avg/5 ) {
            it = lines.erase(it);
            deleted++;
        } else {
            ++it;
        }
    }
    std::cout << "i delete " << deleted << " out of " << linesSize << " liness" << std::endl;
    return bestPoint;
}