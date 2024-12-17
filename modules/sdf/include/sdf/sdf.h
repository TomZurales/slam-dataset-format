#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>
#include <fstream>
#include <string>

#include "sdf/header.h"
#include "sdf/sensor.h"

namespace SDF
{
  class SDF
  {
    Header _header;
    std::vector<std::shared_ptr<Sensor>> _sensors;

  public:
    template <typename T>
    std::shared_ptr<T> addSensor(typename T::Properties properties)
    {
      static_assert(std::is_base_of<Sensor, T>::value, "T must be derived from SDF::sensors::Sensor");
      std::shared_ptr<T> newSensor = std::make_shared<T>(properties);
      _sensors.push_back(newSensor);
      return newSensor;
    }

    int write(std::filesystem::path path);
  };
}