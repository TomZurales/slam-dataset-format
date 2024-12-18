find_package(OpenCV 4.10 REQUIRED)

set(SOURCES
  src/position_leica.cc
)

add_library(position_leica ${SOURCES})

target_include_directories(position_leica
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(position_leica
  PRIVATE common
)