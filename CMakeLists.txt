cmake_minimum_required(VERSION 3.27)
project(slam_dataset_format)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(DO_TEST TRUE)

if(DO_TEST)
  find_package(Catch2 3 REQUIRED)
  include(CTest)
  include(Catch)

  enable_testing()
endif()

add_subdirectory(modules/common)

add_subdirectory(modules/plugins/camera_pinhole_radtan)
add_subdirectory(modules/plugins/imu_6dof_allan)
# add_subdirectory(modules/plugins/position_leica)

add_subdirectory(modules/generator)
add_subdirectory(modules/dataset)

add_subdirectory(modules/util)

# add_executable(slam_dataset_format_test main.cc)
# target_link_libraries(slam_dataset_format_test common camera_pinhole_radtan sdf)
