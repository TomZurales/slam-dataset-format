#include "sdf/sdf/sdf.h"

int SDF::SDF::write(std::filesystem::path path)
{
#ifdef DEBUG
  std::cout << "Writing SDF to " << path << std::endl;
#endif

  std::ofstream outfile = std::ofstream(path, std::ios::binary);
  if (!outfile.is_open())
  {
    return 1;
  }
  std::cout << header.to_string();
  return 3;
}