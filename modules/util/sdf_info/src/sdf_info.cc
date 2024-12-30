#include <iostream>
#include <filesystem>

#include "sdf/sdf.h"
#include "loader.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: sdf_info <sdf_path>" << std::endl;
    exit(1);
  }

  std::filesystem::path sdf_path(argv[1]);
  sdf_path = std::filesystem::canonical(sdf_path);

  // SDF::Generator generator;
  // generator.addSensor<CameraPinholeRadTan>("cam0", props);
  // generator.addSensor<CameraPinholeRadTan>("cam1", props);
  // generator.addSensor<IMU>("imu0", props);
  //
  // generator.addData("cam0", data);
  // generator.addData("cam1", data);
  // generator.addData("imu0", data);

  return 0;
}