#include <iostream>
#include <filesystem>
#include <memory>

#include <yaml-cpp/yaml.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "sdf/generator.h"
#include "sdf/plugins/camera_pinhole_radtan.h"
#include "sdf/plugins/imu_6dof_allan.h"
#include "sdf/transform.h"

void processBody(std::filesystem::path bodyPath, std::shared_ptr<SDF::Generator> generator)
{
}

void processCamera(std::filesystem::path cameraPath, YAML::Node cameraConfig, std::shared_ptr<SDF::Generator> generator)
{
  std::shared_ptr<SDF::sensors::CameraPinholeRadTan> camera(new SDF::sensors::CameraPinholeRadTan());
  auto props = camera->getProps();
  props->name = cameraPath.filename().string();
  // props->transform = SDF::Transform(cameraConfig["T_BS"]["data"].as<std::vector<float>>());

  props->notes = cameraConfig["comment"].as<std::string>();
  props->rate = cameraConfig["rate_hz"].as<float>();
  props->width = cameraConfig["resolution"][0].as<uint32_t>();
  props->height = cameraConfig["resolution"][1].as<uint32_t>();
  std::vector<float> intrinsics = cameraConfig["intrinsics"].as<std::vector<float>>();
  props->fx = intrinsics[0];
  props->fy = intrinsics[1];
  props->cx = intrinsics[2];
  props->cy = intrinsics[3];
  std::vector<float> distortion = cameraConfig["distortion_coefficients"].as<std::vector<float>>();
  props->k1 = distortion[0];
  props->k2 = distortion[1];
  props->p1 = distortion[2];
  props->p2 = distortion[3];

  // props->lazyLoad = true;
  for (std::filesystem::path imagePath : std::filesystem::directory_iterator(cameraPath / "data"))
  {
    std::shared_ptr<SDF::sensors::CameraPinholeRadTanData> cameraData = std::make_shared<SDF::sensors::CameraPinholeRadTanData>();
    cameraData->timestamp = std::stoull(imagePath.filename().stem().string());
    cameraData->image = cv::imread(imagePath.string());
    camera->addData(cameraData);
  }

  generator->addSensor(camera);
}

void processIMU(std::filesystem::path imuPath, YAML::Node imuConfig, std::shared_ptr<SDF::Generator> generator)
{
  std::shared_ptr<SDF::sensors::Imu6dofAllan> imu(new SDF::sensors::Imu6dofAllan());
  auto props = imu->getProps();
  props->name = imuPath.filename().string();
  // props->transform = SDF::Transform(imuConfig["T_BS"]["data"].as<std::vector<float>>());

  props->notes = imuConfig["comment"].as<std::string>();
  props->rate = imuConfig["rate_hz"].as<float>();
  props->gyroscope_noise_density = imuConfig["gyroscope_noise_density"].as<float>();
  props->gyroscope_random_walk = imuConfig["gyroscope_random_walk"].as<float>();
  props->accelerometer_noise_density = imuConfig["accelerometer_noise_density"].as<float>();
  props->accelerometer_random_walk = imuConfig["accelerometer_random_walk"].as<float>();

  // props->lazyLoad = false;

  std::ifstream imuDataFile(imuPath / "data.csv");
  if (!imuDataFile.is_open())
  {
    std::cerr << "Could not open data file for IMU: " << imuPath.string() << std::endl;
    return;
  }

  // TODO: Write an actual CSV parser
  for (std::string line; std::getline(imuDataFile, line);)
  {
    if (line.empty() || line[0] == '#')
    {
      continue;
    }
    std::shared_ptr<SDF::sensors::Imu6dofAllanData> imuData = std::make_shared<SDF::sensors::Imu6dofAllanData>();
    std::istringstream ss(line);
    std::string token;
    std::getline(ss, token, ',');
    imuData->timestamp = std::stoull(token);
    std::getline(ss, token, ',');
    imuData->ax = std::stof(token);
    std::getline(ss, token, ',');
    imuData->ay = std::stof(token);
    std::getline(ss, token, ',');
    imuData->az = std::stof(token);
    std::getline(ss, token, ',');
    imuData->wx = std::stof(token);
    std::getline(ss, token, ',');
    imuData->wy = std::stof(token);
    std::getline(ss, token, ',');
    imuData->wz = std::stof(token);
    imu->addData(imuData);
  }

  generator->addSensor(imu);
}

void processLeica(std::filesystem::path leicaPath, YAML::Node leicaConfig, std::shared_ptr<SDF::Generator> generator)
{
  // std::shared_ptr<SDF::sensors::PositionLeica> leica(new SDF::sensors::PositionLeica());
  // leica->name = leicaPath.filename().string();
  // leica->transform = SDF::Transform(leicaConfig["T_BS"]["data"].as<std::vector<float>>());
  // leica->notes = leicaConfig["comment"].as<std::string>();

  // leica->lazyLoad = false;

  // std::ifstream leicaDataFile(leicaPath / "data.csv");
  // if (!leicaDataFile.is_open())
  // {
  //   std::cerr << "Could not open data file for Leica: " << leicaPath.string() << std::endl;
  //   return;
  // }

  // // TODO: Write an actual CSV parser
  // for (std::string line; std::getline(leicaDataFile, line);)
  // {
  //   if (line.empty() || line[0] == '#')
  //   {
  //     continue;
  //   }
  //   std::shared_ptr<SDF::sensors::PositionLeica::Data> leicaData = std::make_shared<SDF::sensors::PositionLeica::Data>();
  //   std::istringstream ss(line);
  //   std::string token;
  //   std::getline(ss, token, ',');
  //   leicaData->timestamp = std::stoull(token);
  //   std::getline(ss, token, ',');
  //   leicaData->pos_x = std::stof(token);
  //   std::getline(ss, token, ',');
  //   leicaData->pos_y = std::stof(token);
  //   std::getline(ss, token, ',');
  //   leicaData->pos_z = std::stof(token);
  //   leica->data.push_back(leicaData);
  // }

  // generator->addSensor(leica);
}

void processGroundTruth(std::filesystem::path groundTruthPath, YAML::Node groundTruthConfig, std::shared_ptr<SDF::Generator> generator)
{
}

void processSensor(std::filesystem::path sensorPath, std::shared_ptr<SDF::Generator> generator)
{
  YAML::Node sensorConfig = YAML::LoadFile(sensorPath / "sensor.yaml");
  std::string sensor_type = sensorConfig["sensor_type"].as<std::string>();
  if (sensor_type == "camera")
  {
    processCamera(sensorPath, sensorConfig, generator);
  }
  else if (sensor_type == "imu")
  {
    processIMU(sensorPath, sensorConfig, generator);
  }
  else if (sensor_type == "visual-inertial")
  {
    processGroundTruth(sensorPath, sensorConfig, generator);
  }
  else if (sensor_type == "position")
  {
    processLeica(sensorPath, sensorConfig, generator);
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

  // TODO: Reenable, just for testing
  // std::cout << "Do you wish to continue? [Y/n] " << std::ends;

  // char response;
  // std::cin.get(response);
  // if (response != 'Y' && response != 'y' && response != '\n')
  // {
  //   exit(0);
  // }

  std::shared_ptr<SDF::Generator> generator(new SDF::Generator());
  for (std::filesystem::path mav_path : std::filesystem::directory_iterator(input_path))
  {
    for (std::filesystem::path sensor_path : std::filesystem::directory_iterator(mav_path))
    {
      if (!std::filesystem::is_directory(sensor_path))
      {
        processBody(sensor_path, generator); // body.yaml
        continue;
      }
      processSensor(sensor_path, generator);
    }
  }

  generator->write(output_path);

  return 0;
}