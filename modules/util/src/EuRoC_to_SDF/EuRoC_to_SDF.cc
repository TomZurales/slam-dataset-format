#include <iostream>
#include <filesystem>
#include <memory>

#include <yaml-cpp/yaml.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "sdf/sdf.h"
#include "sdf/plugins/pinhole_radtan_camera.h"

void processBody(std::filesystem::path bodyPath, std::shared_ptr<SDF::SDF> sdf)
{
}

void processCamera(std::filesystem::path cameraPath, YAML::Node cameraConfig, std::shared_ptr<SDF::SDF> sdf)
{
  std::shared_ptr<SDF::sensors::PinholeRadTanCamera::Properties> cameraProperties(new SDF::sensors::PinholeRadTanCamera::Properties());
  cameraProperties->name = cameraPath.filename().string();
  cameraProperties->comment = cameraConfig["comment"].as<std::string>();
  cameraProperties->rate = cameraConfig["rate_hz"].as<float>();
  cameraProperties->width = cameraConfig["resolution"][0].as<uint32_t>();
  cameraProperties->height = cameraConfig["resolution"][1].as<uint32_t>();
  std::vector<float> intrinsics = cameraConfig["intrinsics"].as<std::vector<float>>();
  cameraProperties->fx = intrinsics[0];
  cameraProperties->fy = intrinsics[1];
  cameraProperties->cx = intrinsics[2];
  cameraProperties->cy = intrinsics[3];
  std::vector<float> distortion = cameraConfig["distortion_coefficients"].as<std::vector<float>>();
  cameraProperties->k1 = distortion[0];
  cameraProperties->k2 = distortion[1];
  cameraProperties->p1 = distortion[2];
  cameraProperties->p2 = distortion[3];

  std::shared_ptr<SDF::sensors::PinholeRadTanCamera> camera(new SDF::sensors::PinholeRadTanCamera(cameraProperties));

  camera->getProperties()->show();

  size_t numFiles = std::distance(std::filesystem::directory_iterator(cameraPath / "data"), std::filesystem::directory_iterator{});

  for (std::filesystem::path imagePath : std::filesystem::directory_iterator(cameraPath / "data"))
  {
    std::shared_ptr<SDF::sensors::PinholeRadTanCamera::Data> cameraData(new SDF::sensors::PinholeRadTanCamera::Data());
    cameraData->timestamp = std::stoull(imagePath.stem());
    cameraData->image = cv::imread(imagePath.string(), cv::IMREAD_GRAYSCALE);
    camera->data.push_back(cameraData);
  }
}

void processIMU(std::filesystem::path imuPath, YAML::Node imuConfig, std::shared_ptr<SDF::SDF> sdf)
{
}

void processLeica(std::filesystem::path leicaPath, YAML::Node leicaConfig, std::shared_ptr<SDF::SDF> sdf)
{
}

void processGroundTruth(std::filesystem::path groundTruthPath, YAML::Node groundTruthConfig, std::shared_ptr<SDF::SDF> sdf)
{
}

void processSensor(std::filesystem::path sensorPath, std::shared_ptr<SDF::SDF> sdf)
{
  YAML::Node sensorConfig = YAML::LoadFile(sensorPath / "sensor.yaml");
  std::string sensor_type = sensorConfig["sensor_type"].as<std::string>();
  if (sensor_type == "camera")
  {
    processCamera(sensorPath, sensorConfig, sdf);
  }
  else if (sensor_type == "imu")
  {
    processIMU(sensorPath, sensorConfig, sdf);
  }
  else if (sensor_type == "visual-inertial")
  {
    processGroundTruth(sensorPath, sensorConfig, sdf);
  }
  else if (sensor_type == "position")
  {
    processLeica(sensorPath, sensorConfig, sdf);
  }
  else
  {
    std::cerr << "Unknown sensor type: " << sensorConfig["sensor_type"] << std::endl;
  }
}

int main(int argc, char **argv)
{
  if (argc < 2 || argc > 3)
  {
    std::cerr << "Usage: EuRoC_to_SDF <dataset_path> [output_name]" << std::endl;
    exit(1);
  }

  std::filesystem::path input_path(argv[1]);
  input_path = std::filesystem::canonical(input_path);

  if (!std::filesystem::is_directory(input_path / "mav0"))
  {
    std::cerr << "No EuRoC dataset could be found at "
              << std::filesystem::canonical(input_path).string()
              << " . Please check the path and try again" << std::endl;
    exit(1);
  }

  std::filesystem::path output_path(".");
  output_path = std::filesystem::canonical(output_path);

  if (argc == 3)
  {
    if (std::filesystem::path(argv[2]).extension() == ".sdf")
    {
      output_path = output_path / argv[2];
    }
    else
    {
      output_path = output_path / (std::string(argv[2]) + ".sdf");
    }
  }
  else
  {
    output_path = output_path / (input_path.filename().string() + ".sdf");
  }

  if (std::filesystem::exists(output_path))
  {
    std::cerr << "Output file " << output_path.string() << " already exists. Please delete or specify a different output name." << std::endl;
    exit(1);
  }

  std::cout << "EuRoC to SDF Converter" << std::endl;
  std::cout << "Input: " << input_path.string() << std::endl;
  std::cout << "Output: " << output_path.string() << std::endl;
  std::cout << "Do you wish to continue? [Y/n] " << std::ends;

  char response;
  std::cin.get(response);
  if (response != 'Y' && response != 'y' && response != '\n')
  {
    exit(0);
  }

  std::shared_ptr<SDF::SDF> sdf(new SDF::SDF());
  for (std::filesystem::path mav_path : std::filesystem::directory_iterator(input_path))
  {
    for (std::filesystem::path sensor_path : std::filesystem::directory_iterator(mav_path))
    {
      if (!std::filesystem::is_directory(sensor_path))
      {
        processBody(sensor_path, sdf); // body.yaml
        continue;
      }
      processSensor(sensor_path, sdf);
    }
  }

  return 0;
}