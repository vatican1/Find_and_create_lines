cmake_minimum_required(VERSION 3.21)
project(Find_and_create_lines)

set(CMAKE_CXX_STANDARD 17)
include_directories(./include)

find_package(OpenCV REQUIRED)

add_executable(Find_and_create_lines src/main.cpp src/GausianBlur.cpp src/Sobel.cpp include/BlureData.h include/Tests.h src/Tests.cpp include/RemovingExtraLines.h src/RemovingExtraLines.cpp include/AllFilters.h include/EdgeDetector.h src/EdgeDetector.cpp include/HoughTransform.h src/HoughTransform.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Find_and_create_lines ${OpenCV_LIBS})