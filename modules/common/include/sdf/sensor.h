#pragma once

#include <string>
#include <cstdint>

#include "sdf/blob.h"
#include "sdf/transform.h"

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

      virtual bool load() { return false; }
    };

    class Properties
    {
    public:
      virtual ~Properties() = default;

      virtual void show() const = 0;
    };

    std::string name;
    Transform transform;

    Sensor(std::string name, Transform transform) : name(name) {};
    virtual ~Sensor() = default;

    std::vector<std::shared_ptr<Data>> data;
    std::shared_ptr<Properties> properties;
    bool lazyLoad = false;

    virtual std::vector<std::shared_ptr<Data>> getData() const = 0;
    virtual std::shared_ptr<Properties> getProperties() const = 0;
  };
}