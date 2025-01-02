#pragma once

#include <string>
#include <cstdint>

#include "sdf/serializable.h"

namespace SDF
{
  template <typename T>
  class Sensor : public Serializable<T>
  {
    // Forward declare our data and properties classes
  public:
    class Data;
    class Props;

  protected:
    std::shared_ptr<Props> props;
    std::vector<std::shared_ptr<Data>> data;

    uint32_t id;

  public:
    std::shared_ptr<Props> getProps() { return props; }
    std::vector<std::shared_ptr<Data>> getData() { return data; }
    uint32_t getId() { return id; }
    void setId(uint32_t id) { this->id = id; }
  };
}