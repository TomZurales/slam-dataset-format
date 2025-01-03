#pragma once

#include "sdf/sensor/data.h"

#include "sdf/plugins/camera_pinhole_radtan.h"

namespace SDF
{
  namespace sensors
  {
    class CameraPinholeRadTanData : public SensorData
    {
    public:
      cv::Mat image;
      std::filesystem::path imagePath;

      SDF::Bytes toBytes() override;
      static CameraPinholeRadTanData fromBytes(SDF::Bytes bytes);

      bool operator==(const CameraPinholeRadTanData &other) const
      {
        return timestamp == other.timestamp &&
               image.channels() == other.image.channels() &&
               image.rows == other.image.rows &&
               image.cols == other.image.cols &&
               std::equal(image.begin<uchar>(), image.end<uchar>(), other.image.begin<uchar>());
      }

      bool operator!=(const CameraPinholeRadTanData &other) const
      {
        return !(*this == other);
      }
    };
  }
}