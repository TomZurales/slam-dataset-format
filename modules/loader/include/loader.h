#pragma once

#include <filesystem>

#include "sdf/sdf.h"

namespace SDF
{
  class Loader
  {
  public:
    Loader() = default;
    SDF load(std::filesystem::path path);
  };
}