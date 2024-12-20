#pragma once

#include "sdf/serializable.h"

namespace SDF
{
  class Transform : public Serializable
  {
  protected:
    std::vector<float> data;

  public:
    Transform() = default;
    Transform(std::vector<float> data) : data(data) {}

    void show() const
    {
      std::cout << "[";
      for (size_t i = 0; i < data.size(); i++)
      {
        std::cout << data[i];
        if (i < data.size() - 1)
        {
          std::cout << ", ";
        }
      }
      std::cout << "]" << std::endl;
    }

    Bytes toBytes() override
    {
      Bytes bytes = Bytes();
      for (auto value : data)
      {
        bytes.add(value);
      }
      return bytes;
    }
  };
}