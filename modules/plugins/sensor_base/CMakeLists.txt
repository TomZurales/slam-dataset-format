set(SOURCES
  src/sensor_base.cc
)

add_library(sensor_base ${SOURCES})

target_include_directories(sensor_base
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(sensor_base
  PRIVATE common
)

if(DO_TEST)
  add_executable(sensor_base test/sensor_base_test.cc)
  target_link_libraries(sensor_base_test sensor_base Catch2::Catch2WithMain)

  catch_discover_tests(sensor_base_test)
endif()