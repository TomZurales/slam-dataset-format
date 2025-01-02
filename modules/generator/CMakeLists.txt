set(SOURCES
  src/generator.cc
)

add_library(generator SHARED ${SOURCES})

target_include_directories(generator
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(generator
  PUBLIC common
)
