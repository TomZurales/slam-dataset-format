#pragma once

#include <string>

namespace SDF
{
  class Plugin
  {
  private:
    std::string name;

  public:
    Plugin(std::string name) : name(name) {};
  };
}