#pragma once

#include "sdf/bytes.h"

namespace SDF
{
  class Serializable
  {
  public:
    virtual Bytes toBytes() = 0;
  };
}