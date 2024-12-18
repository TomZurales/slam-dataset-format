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

        float gyroscope_noise_density;
        float gyroscope_random_walk;
        float accelerometer_noise_density;
        float accelerometer_random_walk;

        void show() const override
        {
          std::cout << "Comment: " << comment << std::endl;
          std::cout << "Rate: " << rate << " Hz" << std::endl;
          std::cout << "Gyroscope Noise Density: " << gyroscope_noise_density << std::endl;
          std::cout << "Gyroscope Random Walk: " << gyroscope_random_walk << std::endl;
          std::cout << "Accelerometer Noise Density: " << accelerometer_noise_density << std::endl;
          std::cout << "Accelerometer Random Walk: " << accelerometer_random_walk << std::endl;
        }
      };

      IMU6DOFAllan(std::string name, std::shared_ptr<Properties> properties, Transform transform);

      std::vector<std::shared_ptr<Sensor::Data>> getData() const override;
      std::shared_ptr<Sensor::Properties> getProperties() const override;
    };
  }
}