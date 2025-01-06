#pragma once

#include "sdf/sensor/props.h"
#include "sdf/plugins/imu_6dof_allan.h"

namespace SDF
{
  namespace sensors
  {
    class Imu6dofAllanProps : public SensorProps
    {
    public:
      std::string notes;
      float rate;

      float gyroscope_noise_density;
      float gyroscope_random_walk;
      float accelerometer_noise_density;
      float accelerometer_random_walk;

      Bytes toBytes() override;
      static Imu6dofAllanProps fromBytes(Bytes bytes);

      bool operator==(const Imu6dofAllanProps &other) const
      {
        return notes == other.notes &&
               rate == other.rate &&
               gyroscope_noise_density == other.gyroscope_noise_density &&
               gyroscope_random_walk == other.gyroscope_random_walk &&
               accelerometer_noise_density == other.accelerometer_noise_density &&
               accelerometer_random_walk == other.accelerometer_random_walk;
      }
    };
  }
}