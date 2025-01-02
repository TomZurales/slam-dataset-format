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
    class PositionLeica : public Sensor
    {
    public:
      class Data : public Sensor::Data
      {
      public:
        float pos_x;
        float pos_y;
        float pos_z;

        bool load() override
        {
          return true;
        }

        Bytes toBytes() override
        {
          Bytes bytes = Bytes();
          bytes.add(timestamp);
          bytes.add(pos_x);
          bytes.add(pos_y);
          bytes.add(pos_z);
          return bytes;
        }
      };

      std::string notes;

      Bytes toBytes() override;
    };
  }
}