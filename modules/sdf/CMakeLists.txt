set(SOURCES
  src/sdf.cc
)

add_library(sdf SHARED ${SOURCES})

target_include_directories(sdf
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(sdf
  PRIVATE common
)