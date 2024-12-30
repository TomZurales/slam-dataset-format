#include <iostream>
#include <filesystem>

#include "sdf/sdf.h"
#include "loader.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: sdf_info <sdf_path>" << std::endl;
    exit(1);
  }

  std::filesystem::path sdf_path(argv[1]);
  sdf_path = std::filesystem::canonical(sdf_path);

  SDF::Loader loader;
  loader.load(sdf_path);

  return 0;
}