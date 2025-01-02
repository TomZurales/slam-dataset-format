#pragma once

#include "sdf/sensor.h"

namespace SDF
{
  class SensorProps : public Serializable<SensorProps>
  {
  public:
    std::string name;
    Transform transform = Transform();

    virtual ~SensorProps() = default;
  };
}