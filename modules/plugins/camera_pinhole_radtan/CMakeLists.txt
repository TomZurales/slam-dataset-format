find_package(OpenCV 4.10 REQUIRED)

set(SOURCES
  src/camera_pinhole_radtan.cc
)

add_library(camera_pinhole_radtan ${SOURCES})

target_include_directories(camera_pinhole_radtan
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PUBLIC ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(camera_pinhole_radtan
  PUBLIC ${OpenCV_LIBS}
  PUBLIC common
)


if(DO_TEST)
  add_executable(camera_pinhole_radtan_test test/camera_pinhole_radtan_test.cc)
  target_link_libraries(camera_pinhole_radtan_test camera_pinhole_radtan Catch2::Catch2WithMain)

  catch_discover_tests(camera_pinhole_radtan_test)
endif()