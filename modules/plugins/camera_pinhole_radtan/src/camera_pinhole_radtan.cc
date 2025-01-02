#include "sdf/plugins/camera_pinhole_radtan.h"

// std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::CameraPinholeRadTan::getData() const
// {
//   return data;
// }

// void SDF::sensors::CameraPinholeRadTan::show() const
// {
//   std::cout << "CameraPinholeRadTan: " << name << std::endl;

//   std::cout << "Transform: ";
//   transform.show();
//   std::cout << "Comment: " << notes << std::endl;
//   std::cout << "Rate: " << rate << " Hz" << std::endl;
//   std::cout << "Resolution: " << width << "x" << height << std::endl;
//   std::cout << "Intrinsics: " << fx << ", " << fy << ", " << cx << ", " << cy << std::endl;
//   std::cout << "Distortion Coefficients: " << k1 << ", " << k2 << ", " << p1 << ", " << p2 << ", " << k3 << std::endl;
// }

SDF::Bytes SDF::sensors::CameraPinholeRadTan::toBytes()
{
  Bytes bytes = Bytes();
  // bytes.add(props);
  return bytes;
}

SDF::sensors::CameraPinholeRadTan SDF::sensors::CameraPinholeRadTan::fromBytes(Bytes bytes)
{
  SDF::sensors::CameraPinholeRadTan camera = SDF::sensors::CameraPinholeRadTan();
  return camera;
}

// SDF::sensors::CameraPinholeRadTan SDF::sensors::CameraPinholeRadTan::fromBinaryFile(std::ifstream &inputFile)
// {
//   SDF::sensors::CameraPinholeRadTan camera = SDF::sensors::CameraPinholeRadTan();
//   uint32_t name_size;
//   inputFile.read(reinterpret_cast<char *>(&name_size), sizeof(name_size));
//   camera.name.resize(name_size);
//   inputFile.read(reinterpret_cast<char *>(camera.name.data()), name_size);
//   uint32_t notes_size;
//   inputFile.read(reinterpret_cast<char *>(&notes_size), sizeof(notes_size));
//   camera.notes.resize(notes_size);
//   inputFile.read(reinterpret_cast<char *>(camera.notes.data()), notes_size);

//   camera.transform = SDF::Transform::fromBinaryFile(inputFile);
//   inputFile.read(reinterpret_cast<char *>(&camera.rate), sizeof(camera.rate));
//   inputFile.read(reinterpret_cast<char *>(&camera.width), sizeof(camera.width));
//   inputFile.read(reinterpret_cast<char *>(&camera.height), sizeof(camera.height));
//   inputFile.read(reinterpret_cast<char *>(&camera.fx), sizeof(camera.fx));
//   inputFile.read(reinterpret_cast<char *>(&camera.fy), sizeof(camera.fy));
//   inputFile.read(reinterpret_cast<char *>(&camera.cx), sizeof(camera.cx));
//   inputFile.read(reinterpret_cast<char *>(&camera.cy), sizeof(camera.cy));
//   inputFile.read(reinterpret_cast<char *>(&camera.k1), sizeof(camera.k1));
//   inputFile.read(reinterpret_cast<char *>(&camera.k2), sizeof(camera.k2));
//   inputFile.read(reinterpret_cast<char *>(&camera.p1), sizeof(camera.p1));
//   inputFile.read(reinterpret_cast<char *>(&camera.p2), sizeof(camera.p2));
//   inputFile.read(reinterpret_cast<char *>(&camera.k3), sizeof(camera.k3));

//   return camera;
// }