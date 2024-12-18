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

    std::string name;
    Transform transform;
    uint32_t id;

    Sensor() = default;
    virtual ~Sensor() = default;

    virtual void show() const = 0;

    std::vector<std::shared_ptr<Data>> data;
    bool lazyLoad = false;

    virtual std::vector<std::shared_ptr<Data>> getData() const = 0;
  };
}