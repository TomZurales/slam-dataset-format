#pragma once

#include <string>
#include <vector>
#include <memory>

#include "sdf/cereal.h"

namespace SDF
{
  class Plugin
  {
  private:
    std::string name;

    std::vector<std::shared_ptr<Cerial>> serializers;

  public:
    Plugin(std::string name) : name(name) {};
    std::string getName() { return name; }

    void addSerializer(std::shared_ptr<Cerial> serializer) { serializers.push_back(serializer); }
    std::vector<std::shared_ptr<Cerial>> getSerializers() { return serializers; }
  };
}