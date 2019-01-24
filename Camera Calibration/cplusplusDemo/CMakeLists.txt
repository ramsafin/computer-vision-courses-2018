cmake_minimum_required(VERSION 3.10)
project(cameraCalib)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cameraCalib main.cpp)

target_link_libraries(cameraCalib ${OpenCV_LIBS})
