#pragma once

#include <vector>
#include <string>
#include <stdfloat>

#include "sdf/sensor.h"
#include <opencv2/core.hpp>

namespace SDF
{
  namespace sensors
  {
    class PinholeRadTanCamera : public Sensor
    {
    protected:
      class Properties : public Sensor_::Properties
      {
      public:
        uint32_t width;
        uint32_t height;
        uint8_t channels;
        float_t fps; // TODO: Convert to fixed size type
        float_t fx;
        float_t fy;
        float_t cx;
        float_t cy;
        float_t k1;
        float_t k2;
        float_t p1;
        float_t p2;
        float_t k3;
      };

      class Data : public Sensor_::Data
      {
      public:
        uint64_t timestamp;
        cv::Mat image;
      };

      PinholeRadTanCamera();
    };
  }
}