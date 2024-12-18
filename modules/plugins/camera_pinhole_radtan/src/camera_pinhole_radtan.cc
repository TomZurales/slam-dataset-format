#include "sdf/plugins/camera_pinhole_radtan.h"

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::CameraPinholeRadTan::getData() const
{
  return data;
}