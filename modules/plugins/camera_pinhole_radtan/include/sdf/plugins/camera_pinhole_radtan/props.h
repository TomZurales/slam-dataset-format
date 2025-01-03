#pragma once

#include "sdf/sensor/props.h"
#include "sdf/plugins/camera_pinhole_radtan.h"

namespace SDF
{
  namespace sensors
  {
    class CameraPinholeRadTanProps : public SensorProps
    {
    public:
      std::string notes;
      float rate;
      uint32_t width;
      uint32_t height;
      float fx;
      float fy;
      float cx;
      float cy;
      float k1;
      float k2;
      float p1;
      float p2;
      float k3;

      uint32_t imageChannels;
      uint32_t dataType;

      SDF::Bytes toBytes() override;

      static CameraPinholeRadTanProps fromBytes(SDF::Bytes bytes);

      bool operator==(const CameraPinholeRadTanProps &other) const
      {
        return notes == other.notes &&
               rate == other.rate &&
               width == other.width &&
               height == other.height &&
               fx == other.fx &&
               fy == other.fy &&
               cx == other.cx &&
               cy == other.cy &&
               k1 == other.k1 &&
               k2 == other.k2 &&
               p1 == other.p1 &&
               p2 == other.p2 &&
               k3 == other.k3 &&
               imageChannels == other.imageChannels &&
               dataType == other.dataType;
      }

      bool operator!=(const CameraPinholeRadTanProps &other) const
      {
        return !(*this == other);
      }
    };
  }
}