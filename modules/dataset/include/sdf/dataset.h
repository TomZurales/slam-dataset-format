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
  private:
    void readMetadata(std::ifstream &file);
    void readPlugins(std::ifstream &file);
    void readSensors(std::ifstream &file);

    int status = 0;
    std::string message = "";

    std::vector<SDF::Plugin> plugins;
    std::vector<SDF::SensorBase> sensors;

    std::vector<std::string> scanList;

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