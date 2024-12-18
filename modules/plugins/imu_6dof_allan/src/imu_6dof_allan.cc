#include "sdf/plugins/imu_6dof_allan.h"

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::IMU6DOFAllan::getData() const
{
  return data;
}