cmake_minimum_required(VERSION 3.14)
project(OpenCV_move_remove)

set(CMAKE_CXX_STANDARD 17)
FIND_PACKAGE(OpenCV PATHS "/home/keys/progs/opencv/opencv-4.1.0/build"  )

add_executable(OpenCV_move_remove main.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCV_move_remove  ${OpenCV_LIBS})