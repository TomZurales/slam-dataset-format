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

    public:
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

        Blob serialize() override
        {
          Blob blob = Blob(52);
          blob << width;
          blob << height;
          blob << channels;
          blob << fps;
          blob << fx;
          blob << fy;
          blob << cx;
          blob << cy;
          blob << k1;
          blob << k2;
          blob << p1;
          blob << p2;
          blob << k3;
          return blob;
        }
      };

      class Data : public Sensor_::Data
      {
      public:
        uint64_t timestamp;
        cv::Mat image;

        Blob serialize() override
        {
          Blob blob = Blob(8 + image.total() * image.elemSize());
          blob << timestamp;
          blob << image.cols;
          blob << image.rows;
          blob << image.channels();
          blob << image.elemSize();
          blob << image.isContinuous();
          blob << image.total();
          blob << image.data;
          return blob;
        }
      };

      Properties _properties;

      PinholeRadTanCamera(Properties properties) : _properties(properties) {};
    };
  }
}