#pragma once

namespace SDF
{
  class Serializable
  {
  public:
    virtual Blob serialize() = 0;

    // virtual T deserialize(Blob blob) = 0;
  };
}