cmake_minimum_required(VERSION 3.27)
project(slam_dataset_format)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(DEBUG TRUE)

add_subdirectory(modules/common)

add_subdirectory(modules/plugins/camera_pinhole_radtan)
add_subdirectory(modules/plugins/imu_6dof_allan)

add_subdirectory(modules/sdf)

add_subdirectory(modules/util)

# add_executable(slam_dataset_format_test main.cc)
# target_link_libraries(slam_dataset_format_test common camera_pinhole_radtan sdf)
