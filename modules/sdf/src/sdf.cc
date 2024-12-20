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

  for (auto sensor : _sensors)
  {
    outfile << sensor->toBytes();
  }
  for (auto sensor : _sensors)
  {
    for (auto data : sensor->data)
    {
      _data.push(data);
    }
  }
  while (!_data.empty())
  {
    auto data = _data.top();
    _data.pop();
    outfile << data->toBytes();
  }
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