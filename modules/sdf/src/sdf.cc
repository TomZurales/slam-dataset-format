#include "sdf/sdf/sdf.h"

int SDF::SDF::write(std::filesystem::path path)
{
  std::ofstream outfile = std::ofstream(path, std::ios::binary);
  if (!outfile.is_open())
  {
    return 1;
  }

  auto headerBlob = _header.toBlob();
  outfile << *headerBlob;

  // for (auto sensor : _sensors)
  // {
  //   std::cout << "Sensor Name: " << sensor->getProperties()->name << std::endl;
  //   auto sensorBlob = sensor->getProperties()->toBlob();
  //   std::cout << "Blob Length: " << sensor->getProperties()->toBlob().size << std::endl;
  //   outfile << sensorBlob;
  // }
  // for (auto sensor : _sensors)
  // {
  //   for (auto data : sensor->data)
  //   {
  //     auto dataBlob = data->toBlob();
  //     outfile << dataBlob;
  //   }
  // }
  return 3;
}