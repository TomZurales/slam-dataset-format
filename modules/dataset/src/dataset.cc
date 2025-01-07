#include "sdf/dataset.h"

bool verifyChecksum(std::ifstream &file)
{
  uint32_t checksum;
  file.read((char *)&checksum, sizeof(checksum));
  return checksum == 0x51A4DA7A;
}

void SDF::Dataset::readHeader(std::ifstream &file)
{
  if (!verifyChecksum(file))
  {
    std::cerr << "Invalid checksum" << std::endl;
    return;
  }

  std::cout << "Checksum verified" << std::endl;
}

SDF::Dataset SDF::Dataset::Load(std::filesystem::path path)
{
  SDF::Dataset dataset;

  std::ifstream datasetFile(path, std::ios::binary);
  if (!datasetFile.is_open())
  {
    std::cerr << "Could not open dataset file: " << path.string() << std::endl;
    exit(1);
  }

  dataset.readHeader(datasetFile);

  return dataset;
}