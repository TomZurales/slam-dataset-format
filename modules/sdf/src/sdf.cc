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

  // for (auto sensor : _sensors)
  // {
  //   std::cout << "Sensor Name: " << sensor->getProperties()->name << std::endl;
  //   auto sensorBytes = sensor->getProperties()->toBytes();
  //   std::cout << "Bytes Length: " << sensor->getProperties()->toBytes().size << std::endl;
  //   outfile << sensorBytes;
  // }
  // for (auto sensor : _sensors)
  // {
  //   for (auto data : sensor->data)
  //   {
  //     auto dataBytes = data->toBytes();
  //     outfile << dataBytes;
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