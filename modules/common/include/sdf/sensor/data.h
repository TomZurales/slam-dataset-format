#pragma once

#include "sdf/sensor.h"

namespace SDF
{
  template <typename T>
  class Sensor<T>::Data : public Serializable<T>
  {
  public:
    uint64_t timestamp;

    virtual ~Data() = default;
    virtual bool lazyLoad() { return true; }
  };
}