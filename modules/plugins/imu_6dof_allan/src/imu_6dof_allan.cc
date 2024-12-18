#include "sdf/plugins/imu_6dof_allan.h"

SDF::sensors::IMU6DOFAllan::IMU6DOFAllan(std::string name, std::shared_ptr<Properties> properties, Transform transform)
    : Sensor(name, transform)
{
  this->properties = properties;
}

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::IMU6DOFAllan::getData() const
{
  return data;
}

std::shared_ptr<SDF::Sensor::Properties> SDF::sensors::IMU6DOFAllan::getProperties() const
{
  return properties;
}