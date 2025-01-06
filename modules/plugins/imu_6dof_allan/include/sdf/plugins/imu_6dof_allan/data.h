#pragma once

#include "sdf/sensor/data.h"
#include "sdf/plugins/imu_6dof_allan.h"

namespace SDF
{
  namespace sensors
  {
    class Imu6dofAllanData : public SensorData
    {
    public:
      float ax;
      float ay;
      float az;
      float wx;
      float wy;
      float wz;

      Bytes toBytes() override
      {
        Bytes bytes = Bytes();
        bytes.add(timestamp);
        bytes.add(ax);
        bytes.add(ay);
        bytes.add(az);
        bytes.add(wx);
        bytes.add(wy);
        bytes.add(wz);
        return bytes;
      }
    };
  };
}
