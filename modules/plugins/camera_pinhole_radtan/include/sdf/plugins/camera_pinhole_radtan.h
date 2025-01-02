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

namespace SDF
{
  namespace sensors
  {
    class CameraPinholeRadTan : public Sensor
    {
    public:
      Bytes toBytes() override;
      CameraPinholeRadTan fromBytes(Bytes bytes);
    };
  }
}