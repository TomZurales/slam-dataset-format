#pragma once

#include "sdf/sensor/props.h"
#include "sdf/plugins/imu_6dof_allan.h"

namespace SDF
{
  namespace sensors
  {
    class Imu6dofAllanProps : public SensorProps
    {
      std::string notes;
      float rate;

      float gyroscope_noise_density;
      float gyroscope_random_walk;
      float accelerometer_noise_density;
      float accelerometer_random_walk;

      Bytes toBytes() override;
    };
  }
}