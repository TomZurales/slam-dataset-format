#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>
#include <fstream>
#include <string>
#include <queue>

#include "sdf/header.h"
#include "sdf/sensor.h"

namespace SDF
{
  class SDF
  {
    Header _header;
    std::vector<std::shared_ptr<Sensor>> _sensors;

    struct CompareSensorData
    {
      bool operator()(const std::shared_ptr<Sensor::Data> &lhs, const std::shared_ptr<Sensor::Data> &rhs) const
      {
        return lhs->timestamp > rhs->timestamp;
      }
    };

    std::priority_queue<std::shared_ptr<Sensor::Data>, std::vector<std::shared_ptr<Sensor::Data>>, CompareSensorData> _data;

  public:
    SDF() = default;

    void addSensor(std::shared_ptr<Sensor> sensor);

    int write(std::filesystem::path path);

    void show() const;
  };
}