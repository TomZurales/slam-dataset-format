#pragma once

#include <filesystem>

#include "sdf/sdf.h"

namespace SDF
{
  class Loader
  {
    static SDF load(std::filesystem::path path);
  };
}