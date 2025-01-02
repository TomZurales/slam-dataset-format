#pragma once

#include "sdf/bytes.h"

namespace SDF
{
  template <typename T>
  class Serializable
  {
  public:
    virtual ~Serializable() = default;
    virtual Bytes toBytes() = 0;

    T fromBytes(Bytes bytes);
  };
}