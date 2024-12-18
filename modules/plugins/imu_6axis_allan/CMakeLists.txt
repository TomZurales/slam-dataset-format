find_package(OpenCV 4.10 REQUIRED)

set(SOURCES
  src/imu_6axis_allan.cc
)

add_library(imu_6axis_allan ${SOURCES})

target_include_directories(imu_6axis_allan
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(imu_6axis_allan
  PRIVATE common
)