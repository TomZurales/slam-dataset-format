#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdfloat>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <filesystem>
#include <iostream>

#include "sdf/sensor.h"
#include "sdf/blob.h"
#include "sdf/transform.h"

namespace SDF
{
  namespace sensors
  {
    class CameraPinholeRadTan : public Sensor
    {
    public:
      class Data : public Sensor::Data
      {
      public:
        // Define the data members for CameraPinholeRadTan::Data
        cv::Mat image;
        std::filesystem::path imagePath;

        void show() const override
        {
          cv::imshow("Image", image);
          cv::waitKey(1);
        }

        bool load() override
        {
          if (imagePath.empty())
          {
            return false;
          }
          image = cv::imread(imagePath.string());
          if (image.empty())
          {
            return false;
          }
          return true;
        }
      };

      std::string comment;
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

      int imageChannels;
      int dataType;

      std::vector<std::shared_ptr<Sensor::Data>> getData() const override;

      void show() const override;
    };
  }
}