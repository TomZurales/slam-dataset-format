add_executable(EuRoC_to_SDF src/EuRoC_to_SDF/EuRoC_to_SDF.cc)

target_link_libraries(EuRoC_to_SDF PRIVATE sdf)