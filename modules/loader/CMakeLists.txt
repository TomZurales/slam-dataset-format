set(SOURCES
  src/loader.cc
)

add_library(loader SHARED ${SOURCES})

target_include_directories(loader
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(loader
  PUBLIC common
  PUBLIC sdf
)
