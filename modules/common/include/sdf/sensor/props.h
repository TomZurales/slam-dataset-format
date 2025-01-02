#pragma once

#include "sdf/sensor.h"

namespace SDF
{
  class Sensor::Props : public Serializable
  {
  public:
    std::string name;
    Transform transform = Transform();

    virtual ~Props() = default;
  };
}