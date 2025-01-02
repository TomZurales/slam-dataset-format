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

namespace SDF
{
  namespace sensors
  {
    class IMU6DOFAllan : public Sensor
    {
    public:
      class Data : public Sensor::Data
      {
      public:
        float ax;
        float ay;
        float az;
        float wx;
        float wy;
        float wz;

        bool load() override
        {
          return true;
        }

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