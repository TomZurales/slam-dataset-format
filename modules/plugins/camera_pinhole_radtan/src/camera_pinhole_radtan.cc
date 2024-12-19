#include "sdf/plugins/camera_pinhole_radtan.h"

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::CameraPinholeRadTan::getData() const
{
  return data;
}

void SDF::sensors::CameraPinholeRadTan::show() const
{
  std::cout << "CameraPinholeRadTan: " << name << std::endl;

  std::cout << "Transform: ";
  transform.show();
  std::cout << "Comment: " << notes << std::endl;
  std::cout << "Rate: " << rate << " Hz" << std::endl;
  std::cout << "Resolution: " << width << "x" << height << std::endl;
  std::cout << "Intrinsics: " << fx << ", " << fy << ", " << cx << ", " << cy << std::endl;
  std::cout << "Distortion Coefficients: " << k1 << ", " << k2 << ", " << p1 << ", " << p2 << ", " << k3 << std::endl;
}

SDF::Blob SDF::sensors::CameraPinholeRadTan::serialize()
{
  return Blob(1);
}