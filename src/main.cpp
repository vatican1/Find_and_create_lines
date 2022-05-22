#include <iostream>
#include <string>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "BlureData.h"

#include "Tests.h"
#include "AllFilters.h"





int main() {
    std::string picturesNames[] = {"Helsinki_1.JPEG", "Helsinki_2.JPEG", "Saint-Petersburg_1.JPEG",
                                   "Saint-Petersburg_2.JPEG", "Saint-Petersburg_3.JPEG", "Tbilisi_1.JPEG"};
    cv::Mat src = cv::imread("data/" + picturesNames[0]);
    if (src.empty()) {
        std::cout << "Error loading src1" << std::endl;
        return -1;
    }


    AllTransforms a(src);





    cv::waitKey(0);


    return 0;
}



