#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>
#include <fstream>
#include <string>
#include <queue>

#include "sdf/generator/header.h"
#include "sdf/sensor.h"
#include "sdf/sensor/data.h"

namespace SDF
{
  class Generator
  {
    Header _header;
    std::vector<std::shared_ptr<SensorBase>> _sensors;

    struct CompareSensorData
    {
      bool operator()(const std::shared_ptr<SensorData> &lhs, const std::shared_ptr<SensorData> &rhs) const
      {
        return lhs->timestamp > rhs->timestamp;
      }
    };

    std::priority_queue<std::shared_ptr<SensorData>, std::vector<std::shared_ptr<SensorData>>, CompareSensorData> _data;

  public:
    Generator() = default;

    void addSensor(std::shared_ptr<SensorBase> sensor);

    int write(std::filesystem::path path);

    void show() const;
  };
}