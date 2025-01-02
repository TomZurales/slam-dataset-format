#pragma once

#include "sdf/sensor.h"

namespace SDF
{
  class SensorData : public Serializable<SensorData>
  {
  public:
    uint64_t timestamp;

    virtual ~SensorData() = default;
    virtual bool lazyLoad() { return true; }
  };
}