#include "sdf/plugins/camera_pinhole_radtan.h"

SDF::sensors::CameraPinholeRadTan::CameraPinholeRadTan(std::string name, std::shared_ptr<Properties> properties, Transform transform)
    : Sensor(name, transform)
{
  this->properties = properties;
}

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::CameraPinholeRadTan::getData() const
{
  return data;
}

std::shared_ptr<SDF::Sensor::Properties> SDF::sensors::CameraPinholeRadTan::getProperties() const
{
  return properties;
}