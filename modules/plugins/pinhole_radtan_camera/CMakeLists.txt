find_package(OpenCV 4.10 REQUIRED)

set(SOURCES
  src/pinhole_radtan_camera.cc
)

add_library(pinhole_radtan_camera ${SOURCES})

target_include_directories(pinhole_radtan_camera
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PUBLIC ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(pinhole_radtan_camera
  PUBLIC ${OpenCV_LIBS}
  PRIVATE common
)