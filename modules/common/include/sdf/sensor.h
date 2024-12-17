#pragma once

#include <string>
#include <cstdint>

#include "sdf/blob.h"
#include "sdf/sensor/data.h"
#include "sdf/sensor/properties.h"

namespace SDF
{
  class Sensor
  {
  public:
    virtual ~Sensor() = default;

    virtual std::vector<std::shared_ptr<Sensor_::Data>> getData() const = 0;
    virtual std::shared_ptr<Sensor_::Properties> getProperties() const = 0;

  public:
    std::shared_ptr<Sensor_::Properties> _properties;
    std::vector<std::shared_ptr<Sensor_::Data>> _data;
  };
}