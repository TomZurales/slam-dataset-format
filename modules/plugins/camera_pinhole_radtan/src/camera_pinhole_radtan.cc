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

SDF::Bytes SDF::sensors::CameraPinholeRadTan::toBytes()
{
  Bytes bytes = Bytes();
  bytes.add((uint32_t)name.size());
  bytes.add(name);
  bytes.add(transform);
  bytes.add((uint32_t)notes.size());
  bytes.add(notes);

  bytes.add(rate);
  bytes.add(width);
  bytes.add(height);
  bytes.add(fx);
  bytes.add(fy);
  bytes.add(cx);
  bytes.add(cy);
  bytes.add(k1);
  bytes.add(k2);
  bytes.add(p1);
  bytes.add(p2);
  bytes.add(k3);

  bytes.add(imageChannels);
  bytes.add(dataType);
  return bytes;
}

static std::shared_ptr<SDF::sensors::CameraPinholeRadTan> SDF::sensors::CameraPinholeRadTan::fromBinaryFile(std::ifstream &inputFile)
{
  SDF::sensors::CameraPinholeRadTan camera = SDF::sensors::CameraPinholeRadTan();
  uint32_t name_size;
  inputFile.read(reinterpret_cast<char *>(&name_size), sizeof(name_size));
  camera.name.resize(name_size);
  inputFile.read(reinterpret_cast<char *>(camera.name.data()), name_size);

  return camera;
}