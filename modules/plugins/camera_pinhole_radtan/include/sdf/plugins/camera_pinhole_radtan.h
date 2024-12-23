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
    class CameraPinholeRadTan : public Sensor, public Serializable
    {
    public:
      class Data : public Sensor::Data
      {
        cv::Mat image;
        std::filesystem::path imagePath;

      public:
        Data(uint64_t timestamp, std::filesystem::path imagePath)
        {
          this->imagePath = imagePath;
          this->timestamp = timestamp;
        }

        Data(uint64_t timestamp, cv::Mat image)
        {
          this->image = image;
          this->timestamp = timestamp;
        }

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

          std::vector<uint8_t> buf;
          cv::imencode(".webp", image, buf, {cv::IMWRITE_WEBP_QUALITY, 100});

          bytes.add(buf.size());
          for (size_t i = 0; i < buf.size(); i++)
          {
            bytes.add(buf[i]);
          }

          return bytes;
        }

        static std::shared_ptr<Data> fromBinaryFile(std::ifstream &inputFile)
        {
          uint64_t timestamp;
          inputFile.read(reinterpret_cast<char *>(&timestamp), sizeof(timestamp));

          uint32_t size;
          inputFile.read(reinterpret_cast<char *>(&size), sizeof(size));

          std::vector<uint8_t> buf(size);
          inputFile.read(reinterpret_cast<char *>(buf.data()), size);

          cv::Mat image = cv::imdecode(buf, cv::IMREAD_COLOR);

          return std::make_shared<Data>(timestamp, image);
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

      static std::shared_ptr<CameraPinholeRadTan> fromBinaryFile(std::ifstream &inputFile);
    };
  }