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
#include "sdf/bytes.h"
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

        Bytes toBytes() override
        {
          Bytes bytes = Bytes();
          bytes.add(timestamp);
          load();
          bytes.add(image.rows);
          bytes.add(image.cols);
          bytes.add(image.channels());
          for (int i = 0; i < image.rows; i++)
          {
            for (int j = 0; j < image.cols; j++)
            {
              for (int k = 0; k < image.channels(); k++)
              {
                bytes.add(image.at<cv::Vec3b>(i, j)[k]);
              }
            }
          }

          return bytes;
        }
      };

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

      std::vector<std::shared_ptr<Sensor::Data>> getData() const override;

      void show() const override;

      Bytes toBytes() override;
    };
  }
}