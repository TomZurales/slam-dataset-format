#pragma once

#include <iostream>

#include "sdf/sdf/header.h"
#include "sdf/sdf/sensor.h"

#include <filesystem>
#include <fstream>

namespace SDF
{
  class SDF
  {
    Header header;

  public:
    void addSensor(Sensor sensor);
    int write(std::filesystem::path path);
  };
}