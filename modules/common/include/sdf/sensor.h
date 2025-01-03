#pragma once

#include <string>
#include <cstdint>

#include "sdf/serializable.h"
#include "sdf/sensor/data.h"
#include "sdf/sensor/props.h"

namespace SDF
{
  class SensorBase
  {
    uint32_t id;

  public:
    virtual ~SensorBase() = default;
    uint32_t getId() { return id; }
    void setId(uint32_t id) { this->id = id; }

    virtual std::shared_ptr<SensorProps> getProps() = 0;
    virtual std::vector<std::shared_ptr<SensorData>> getData() = 0;
  };

  template <typename T_Data, typename T_Props>
  class Sensor : public Serializable, public SensorBase
  {
  protected:
    std::shared_ptr<T_Props> props;
    std::vector<std::shared_ptr<T_Data>> data;

  public:
    std::shared_ptr<SensorProps> getProps() override { return props; }
    std::vector<std::shared_ptr<SensorData>> getData() override
    {
      std::vector<std::shared_ptr<SensorData>> sensorData;
      for (const auto &d : data)
      {
        sensorData.push_back(std::static_pointer_cast<SensorData>(d));
      }
      return sensorData;
    }
  };
}