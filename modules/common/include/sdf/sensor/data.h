#pragma once

namespace SDF
{
  class SensorData : public Serializable
  {
  public:
    uint64_t timestamp;

    virtual ~SensorData() = default;
    virtual bool lazyLoad() { return true; }
  };
}