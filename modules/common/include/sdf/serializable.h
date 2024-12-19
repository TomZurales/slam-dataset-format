#pragma once

namespace SDF
{
  class Serializable
  {
  public:
    virtual Blob serialize() = 0;
  };
}