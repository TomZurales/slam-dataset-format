#pragma once

#include "sdf/sensor.h"

namespace SDF
{
  class Sensor::Data : public Serializable
  {
  public:
    uint64_t timestamp;

    virtual ~Data() = default;
    virtual bool lazyLoad() { return true; }
  };
}