cmake_minimum_required(VERSION 3.16)
project(WaifuDetect)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
add_executable(WaifuDetect main.cpp)

target_include_directories(WaifuDetect PRIVATE)
target_link_libraries(WaifuDetect ${OpenCV_LIBS})