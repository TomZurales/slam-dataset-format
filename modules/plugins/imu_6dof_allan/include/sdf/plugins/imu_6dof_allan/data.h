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

      Bytes toBytes() override;
      static Imu6dofAllanData fromBytes(Bytes bytes);

      bool operator==(const Imu6dofAllanData &other) const
      {
        return timestamp == other.timestamp &&
               ax == other.ax &&
               ay == other.ay &&
               az == other.az &&
               wx == other.wx &&
               wy == other.wy &&
               wz == other.wz;
      }
    };
  };
}
