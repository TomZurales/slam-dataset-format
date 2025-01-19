#include "sdf/generator.h"

void SDF::Generator::addSensor(std::shared_ptr<SensorBase> sensor)
{
  sensor->setId(_sensors.size());
  _sensors.push_back(sensor);
}

int SDF::Generator::write(std::filesystem::path path)
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
    for (auto data : sensor->_getData())
    {
      _data.push(data);
    }
  }
  int count = _data.size();
  while (!_data.empty())
  {
    if ((count - _data.size()) % 100 == 0)
      std::cout << "Writing " << count - _data.size() << " of " << count << " sensor data" << std::endl;
    auto data = _data.top();
    _data.pop();
    // outfile << data->toBytes();
  }
  return 3;
}

void SDF::Generator::show() const
{
  std::cout << "Sensors:" << std::endl;
  for (auto sensor : _sensors)
  {
    // sensor->show();
  }
}