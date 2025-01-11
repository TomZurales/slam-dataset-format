#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "sdf/plugin.h"
#include "sdf/bytes.h"
#include "sdf/sensor.h"

namespace SDF
{
  class Dataset
  {
    enum Status
    {
      OK = 0,
      ERROR
    };

  private:
    void readMetadata();
    void readPlugins();
    void readSensors();

    bool verifyChecksum();

    Status status = Status::OK;
    std::string message = "";

    std::vector<SDF::Plugin> plugins;
    std::vector<SDF::SensorBase> sensors;

    std::vector<std::string> scanList;

    std::ifstream file;
    size_t fileSize = 0;

    template <typename T>
    void read(T *value)
    {
      if (file.tellg() + sizeof(T) >= fileSize)
      {
        status = Status::ERROR;
        message = "Unexpected end of file";
        return;
      }
      file.read(reinterpret_cast<char *>(&value), sizeof(T));
    }

    void read_raw(void *buf, size_t size)
    {
      file.read(reinterpret_cast<char *>(buf), size);
    }

  public:
    static Dataset Load(const std::filesystem::path &);

    const int getStatus() { return status; }

    void setScanList(std::vector<std::string>);

    std::vector<SDF::SensorBase> getUntilNext(std::string);

    void addPlugin(SDF::Plugin plugin) { plugins.push_back(plugin); }
    std::vector<SDF::Plugin> getPlugins() { return plugins; }

    // void addSensor(SDF::SensorBase sensor) { sensors.push_back(sensor); }
    // std::vector<SDF::SensorBase> getSensors() { return sensors; }

    void write(std::filesystem::path);
  };
}