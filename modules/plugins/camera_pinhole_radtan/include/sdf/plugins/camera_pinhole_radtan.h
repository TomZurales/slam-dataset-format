#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdfloat>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "sdf/sensor.h"
#include "sdf/bytes.h"
#include "sdf/transform.h"
#include "sdf/plugins/camera_pinhole_radtan/props.h"
#include "sdf/plugins/camera_pinhole_radtan/data.h"

namespace SDF
{
  namespace sensors
  {
    class CameraPinholeRadTan : public Sensor<CameraPinholeRadTanData, CameraPinholeRadTanProps>
    {
    public:
      CameraPinholeRadTan() = default;
      ~CameraPinholeRadTan() = default;
    };
  }
}