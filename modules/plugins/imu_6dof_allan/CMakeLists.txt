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

if(DO_TEST)
  add_executable(imu_6dof_allan_test test/imu_6dof_allan_test.cc)
  target_link_libraries(imu_6dof_allan_test imu_6dof_allan Catch2::Catch2WithMain)

  catch_discover_tests(imu_6dof_allan_test)
endif()