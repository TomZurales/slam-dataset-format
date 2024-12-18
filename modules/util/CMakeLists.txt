find_package(yaml-cpp REQUIRED)

add_executable(EuRoC_to_SDF src/EuRoC_to_SDF/EuRoC_to_SDF.cc)

target_link_libraries(EuRoC_to_SDF PRIVATE sdf pinhole_radtan_camera yaml-cpp::yaml-cpp)