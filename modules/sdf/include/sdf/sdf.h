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
    void addSensor(std::shared_ptr<Sensor> sensor);

    int write(std::filesystem::path path);

    void show() const;
  };
}