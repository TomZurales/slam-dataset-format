#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "sdf/plugin.h"
#include "sdf/bytes.h"

namespace SDF
{
  class Dataset
  {
  private:
    void readHeader(std::ifstream &file);

    std::vector<SDF::Plugin> plugins;

  public:
    static Dataset Load(std::filesystem::path path);
  };
}