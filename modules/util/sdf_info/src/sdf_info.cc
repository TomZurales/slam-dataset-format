#include <iostream>
#include <filesystem>

#include "sdf/generator.h"
// #include "loader.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: sdf_info <sdf_path>" << std::endl;
    exit(1);
  }

  std::filesystem::path sdf_path(argv[1]);
  sdf_path = std::filesystem::canonical(sdf_path);

  // SDF::SDF sdf;
  // sdf.addSensor<CameraPinholeRadTan>("cam0", props);
  // sdf.addSensor<CameraPinholeRadTan>("cam1", props);
  // sdf.addSensor<IMU>("imu0", props);
  //
  // sdf.addData("cam0", data);
  // sdf.addData("cam1", data);
  // sdf.addData("imu0", data);

  return 0;
}