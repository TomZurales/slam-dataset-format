find_package(OpenCV 4.10 REQUIRED)

set(SOURCES
  src/imu_6dof_allan.cc
)

add_library(imu_6dof_allan ${SOURCES})

target_include_directories(imu_6dof_allan
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(imu_6dof_allan
  PRIVATE common
)