#pragma once

#include <string>
#include <cstdint>

#include "sdf/blob.h"

namespace SDF
{
  class Sensor
  {
  public:
    class Data
    {
    public:
      virtual ~Data() = default;

      uint64_t timestamp;

      virtual void show() const = 0;
    };

    class LazyData
    {
    public:
      virtual ~LazyData() = default;
    };

    class Properties
    {
    public:
      virtual ~Properties() = default;

      virtual void show() const = 0;
    };

    Sensor() = default;
    virtual ~Sensor() = default;

    std::vector<std::shared_ptr<Data>> data;
    std::shared_ptr<Properties> properties;
    bool lazyLoad = false;

    virtual std::vector<std::shared_ptr<Data>>
    getData() const = 0;
    virtual std::shared_ptr<Properties> getProperties() const = 0;
  };
}