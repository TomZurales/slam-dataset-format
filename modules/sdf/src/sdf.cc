#include "sdf/sdf.h"

void SDF::SDF::addSensor(std::shared_ptr<Sensor> sensor)
{
  sensor->id = _sensors.size();
  _sensors.push_back(sensor);
}

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

void SDF::SDF::show() const
{
  std::cout << "Sensors:" << std::endl;
  for (auto sensor : _sensors)
  {
    sensor->show();
  }
}