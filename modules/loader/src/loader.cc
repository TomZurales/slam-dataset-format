#include "loader.h"

SDF::SDF SDF::Loader::load(std::filesystem::path path)
{
  std::cout << "Loading SDF from " << path.string() << std::endl;
  return SDF();
}