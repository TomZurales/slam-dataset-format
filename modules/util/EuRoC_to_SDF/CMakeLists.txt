find_package(yaml-cpp REQUIRED)

add_executable(EuRoC_to_SDF src/EuRoC_to_SDF.cc)

target_link_libraries(EuRoC_to_SDF PRIVATE sdf camera_pinhole_radtan imu_6dof_allan position_leica yaml-cpp::yaml-cpp)