#pragma once

#include "sdf/bytes.h"

namespace SDF
{
  class Serializable
  {
  public:
    virtual ~Serializable() = default;
    virtual Bytes toBytes() = 0;

    template <typename T>
    T fromBytes(Bytes bytes);
  };
}