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
  };
}