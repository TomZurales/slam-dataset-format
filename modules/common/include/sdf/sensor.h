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

    virtual std::shared_ptr<SensorProps> _getProps() = 0;
    virtual std::vector<std::shared_ptr<SensorData>> _getData() = 0;
  };

  template <typename T_Data, typename T_Props>
  class Sensor : public SensorBase
  {
  protected:
    std::shared_ptr<T_Props> props = std::make_shared<T_Props>();
    std::vector<std::shared_ptr<T_Data>> data = std::vector<std::shared_ptr<T_Data>>();

  public:
    std::shared_ptr<SensorProps> _getProps() override { return props; }
    std::vector<std::shared_ptr<SensorData>> _getData() override
    {
      std::vector<std::shared_ptr<SensorData>> sensorData;
      for (auto d : data)
      {
        sensorData.push_back(d);
      }
      return sensorData;
    }

    std::shared_ptr<T_Props> getProps() { return props; }
    std::vector<std::shared_ptr<T_Data>> getData() { return data; }
    void addData(std::shared_ptr<T_Data> data) { this->data.push_back(data); }
    };
}