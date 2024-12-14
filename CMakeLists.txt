cmake_minimum_required(VERSION 3.28)
project(slam_dataset_format)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(modules/sdf)

add_executable(slam_dataset_format_test main.cc)
target_link_libraries(slam_dataset_format_test sdf)