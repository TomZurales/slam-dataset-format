#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdfloat>
#include <filesystem>
#include <iostream>

#include "sdf/sensor.h"
#include "sdf/blob.h"
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

        void show() const override
        {
        }

        bool load() override
        {
          return true;
        }
      };

      std::string notes;

      std::vector<std::shared_ptr<Sensor::Data>> getData() const override;

      void show() const override;
    };
  }
}