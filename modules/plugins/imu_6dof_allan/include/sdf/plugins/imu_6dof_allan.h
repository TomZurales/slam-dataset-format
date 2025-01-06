#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdfloat>
#include <filesystem>
#include <iostream>

#include "sdf/sensor.h"
#include "sdf/sensor/data.h"
#include "sdf/bytes.h"
#include "sdf/transform.h"
#include "sdf/plugins/imu_6dof_allan/props.h"
#include "sdf/plugins/imu_6dof_allan/data.h"

namespace SDF
{
  namespace sensors
  {
    class Imu6dofAllan : public Sensor<Imu6dofAllanData, Imu6dofAllanProps>
    {
    public:
      Imu6dofAllan() = default;
      ~Imu6dofAllan() = default;
    };
  }
}