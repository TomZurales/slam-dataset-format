#include "sdf/plugins/sensor_base.h"

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::SensorBase::getData() const
{
  return data;
}

void SDF::sensors::SensorBase::show() const
{
}

SDF::Bytes SDF::sensors::SensorBase::toBytes()
{
  Bytes bytes = Bytes();
  return bytes;
}