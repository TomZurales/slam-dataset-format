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
    };
  }
}