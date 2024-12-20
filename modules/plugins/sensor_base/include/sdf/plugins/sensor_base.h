#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdfloat>
#include <filesystem>
#include <iostream>

#include "sdf/sensor.h"
#include "sdf/bytes.h"
#include "sdf/transform.h"

namespace SDF
{
  namespace sensors
  {
    class SensorBase : public Sensor
    {
    public:
      class Data : public Sensor::Data
      {
      public:
        void show() const override
        {
        }

        Bytes toBytes() override
        {
          Bytes bytes = Bytes();
          return bytes;
        }
      };

      std::string notes;

      std::vector<std::shared_ptr<Sensor::Data>> getData() const override;

      void show() const override;

      Bytes toBytes() override;
    };
  }
}