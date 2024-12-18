#include "sdf/plugins/imu_6axis_allan.h"

SDF::sensors::IMU6AxisAllan::IMU6AxisAllan(std::string name, std::shared_ptr<Properties> properties, Transform transform)
    : Sensor(name, transform)
{
  this->properties = properties;
}

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::IMU6AxisAllan::getData() const
{
  return data;
}

std::shared_ptr<SDF::Sensor::Properties> SDF::sensors::IMU6AxisAllan::getProperties() const
{
  return properties;
}