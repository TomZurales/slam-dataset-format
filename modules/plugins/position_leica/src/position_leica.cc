#include "sdf/plugins/position_leica.h"

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::PositionLeica::getData() const
{
  return data;
}

void SDF::sensors::PositionLeica::show() const
{
  std::cout << "PositionLeica: " << name << std::endl;

  std::cout << "Transform: ";
  transform.show();
  std::cout << "Comment: " << notes << std::endl;
}

SDF::Bytes SDF::sensors::PositionLeica::toBytes()
{
  Bytes bytes = Bytes();
  bytes.add(name);
  bytes.add(transform);
  bytes.add(notes);
  return bytes;
}