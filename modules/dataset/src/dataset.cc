#include "sdf/dataset.h"

bool verifyChecksum(std::ifstream &file)
{
  uint32_t checksum;
  file.read((char *)&checksum, sizeof(checksum));
  return checksum == 0x51A3DA7A;
}

void SDF::Dataset::readPlugins(std::ifstream &file)
{
  uint32_t numPlugins;
  file.read((char *)&numPlugins, sizeof(numPlugins));

  for (int i = 0; i < numPlugins; i++)
  {
    uint32_t pluginNameLength;
    file.read((char *)&pluginNameLength, sizeof(pluginNameLength));

    std::string pluginName;
    pluginName.resize(pluginNameLength);
    file.read(pluginName.data(), pluginNameLength);

    plugins.push_back(SDF::Plugin(pluginName));
  }
}

void SDF::Dataset::readSensors(std::ifstream &file)
{
  uint32_t numSensors;
  file.read((char *)&numSensors, sizeof(numSensors));
}

void SDF::Dataset::readMetadata(std::ifstream &file)
{
  readPlugins(file);
  readSensors(file);
}

SDF::Dataset SDF::Dataset::Load(const std::filesystem::path &path)
{
  SDF::Dataset dataset;

  std::ifstream datasetFile(path, std::ios::binary);
  if (!datasetFile.is_open())
  {
    dataset.status = 2;
    dataset.message = "Failed to open file " + path.string();
    return dataset;
  }

  if (!verifyChecksum(datasetFile))
  {
    dataset.status = 1;
    dataset.message = "Checksum failed";
  }

  dataset.readMetadata(datasetFile);

  return dataset;
}

void SDF::Dataset::write(std::filesystem::path path)
{
  std::ofstream datasetFile(path, std::ios::binary);
  uint32_t header = 0x51A3DA7A;
  datasetFile.write(reinterpret_cast<const char *>(&header), sizeof(header));

  uint32_t numPlugins = plugins.size();
  datasetFile.write(reinterpret_cast<const char *>(&numPlugins), sizeof(numPlugins));
  for (Plugin &plugin : plugins)
  {
    uint32_t pluginNameLength = plugin.getName().size();
    datasetFile.write(reinterpret_cast<const char *>(&pluginNameLength), sizeof(pluginNameLength));
    datasetFile.write(plugin.getName().data(), pluginNameLength);
  }

  uint32_t numSensors = sensors.size();
  datasetFile.write(reinterpret_cast<const char *>(&numSensors), sizeof(numSensors));

  datasetFile.close();
}