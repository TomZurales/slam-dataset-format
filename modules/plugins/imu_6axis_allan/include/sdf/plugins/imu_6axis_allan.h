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
    class IMU6AxisAllan : public Sensor
    {
    public:
      class Data : public Sensor::Data
      {
      public:
        // Define the data members for PinholeRadTanCamera::Data
        std::filesystem::path imagePath;

        void show() const override
        {
        }

        bool load() override
        {
          return true;
        }
      };

      class Properties : public Sensor::Properties
      {
      public:
        std::string comment;
        float rate;
        uint32_t width;
        uint32_t height;
        float fx;
        float fy;
        float cx;
        float cy;
        float k1;
        float k2;
        float p1;
        float p2;
        float k3;

        int imageChannels;
        int dataType;

        void show() const override
        {
          std::cout << "Comment: " << comment << std::endl;
          std::cout << "Rate: " << rate << " Hz" << std::endl;
          std::cout << "Resolution: " << width << "x" << height << std::endl;
          std::cout << "Intrinsics: " << fx << ", " << fy << ", " << cx << ", " << cy << std::endl;
          std::cout << "Distortion Coefficients: " << k1 << ", " << k2 << ", " << p1 << ", " << p2 << ", " << k3 << std::endl;
        }
      };

      IMU6AxisAllan(std::string name, std::shared_ptr<Properties> properties, Transform transform);

      std::vector<std::shared_ptr<Sensor::Data>> getData() const override;
      std::shared_ptr<Sensor::Properties> getProperties() const override;
    };
  }
}