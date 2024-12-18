#include "sdf/plugins/pinhole_radtan_camera.h"

SDF::sensors::PinholeRadTanCamera::PinholeRadTanCamera(std::shared_ptr<Properties> properties)
    : Sensor()
{
  this->properties = properties;
}

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::PinholeRadTanCamera::getData() const
{
  return data;
}

std::shared_ptr<SDF::Sensor::Properties> SDF::sensors::PinholeRadTanCamera::getProperties() const
{
  return properties;
}