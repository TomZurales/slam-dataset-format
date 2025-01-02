#pragma once

#include "sdf/sensor/data.h"

#include "sdf/plugins/camera_pinhole_radtan.h"

class SDF::sensors::CameraPinholeRadTan::Data : public Sensor::Data
{
  cv::Mat image;
  std::filesystem::path imagePath;

public:
};
