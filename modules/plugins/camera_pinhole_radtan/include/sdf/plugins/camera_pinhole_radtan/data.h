#pragma once

#include "sdf/sensor/data.h"

#include "sdf/plugins/camera_pinhole_radtan.h"

namespace SDF
{
  namespace sensors
  {
    class CameraPinholeRadTanData : public SensorData
    {
      cv::Mat image;
      std::filesystem::path imagePath;

    public:
    };
  }
}