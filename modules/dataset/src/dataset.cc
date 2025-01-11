#include "sdf/dataset.h"

bool SDF::Dataset::verifyChecksum()
{
  uint32_t checksum;
  read(&checksum);
  return checksum == 0x51A3DA7A;
}

void SDF::Dataset::readPlugins()
{
  uint32_t numPlugins;
  read(&numPlugins);

  for (int i = 0; i < numPlugins; i++)
  {
    uint32_t pluginNameLength;
    read(&pluginNameLength);

    std::string pluginName;
    pluginName.resize(pluginNameLength);
    read_raw(pluginName.data(), pluginNameLength);

    plugins.push_back(SDF::Plugin(pluginName));
  }
}

void SDF::Dataset::readSensors()
{
  uint32_t numSensors;
  read(&numSensors);
  for (int i = 0; i < numSensors; i++)
  {
    uint32_t pluginId;
    read(&pluginId);
    uint32_t serializerId;
    read(&serializerId);
    plugins[pluginId].getSerializers()[serializerId]->deserialize(file);
  }
}

void SDF::Dataset::readMetadata()
{
  readPlugins();
  readSensors();
}

SDF::Dataset SDF::Dataset::Load(const std::filesystem::path &path)
{
  SDF::Dataset dataset;

  dataset.file = std::ifstream(path, std::ios::binary);
  if (!dataset.file.is_open())
  {
    dataset.status = Status::ERROR;
    dataset.message = "Failed to open file " + path.string();
    return dataset;
  }

  dataset.file.seekg(0, std::ios::end);
  dataset.fileSize = dataset.file.tellg();
  dataset.file.seekg(0, std::ios::beg);

  if (!dataset.verifyChecksum())
  {
    dataset.status = Status::ERROR;
    dataset.message = "Checksum read failed";
    return dataset;
  }

  dataset.readMetadata();

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