#pragma once

#include "sdf/bytes.h"

namespace SDF
{
  class Serializable
  {
  public:
    virtual ~Serializable() = default;
    virtual Bytes toBytes() = 0;
    static std::shared_ptr<Serializable> fromBinaryFile(std::ifstream &inputFile);
  };
}