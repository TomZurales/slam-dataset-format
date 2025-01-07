add_library(dataset src/dataset.cc)
target_include_directories(dataset PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(dataset PUBLIC common)

if(DO_TEST)
  add_executable(dataset_test test/dataset_test.cc)
  target_link_libraries(dataset_test dataset Catch2::Catch2WithMain)

  catch_discover_tests(dataset_test)
endif()