#pragma once

namespace SDF
{
  class Transform
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
  };
}