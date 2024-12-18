#include <iostream>
#include <filesystem>
#include <memory>

#include <yaml-cpp/yaml.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "sdf/sdf.h"
#include "sdf/plugins/camera_pinhole_radtan.h"
#include "sdf/plugins/imu_6dof_allan.h"
#include "sdf/transform.h"

void processBody(std::filesystem::path bodyPath, std::shared_ptr<SDF::SDF> sdf)
{
}

void processCamera(std::filesystem::path cameraPath, YAML::Node cameraConfig, std::shared_ptr<SDF::SDF> sdf)
{
  std::shared_ptr<SDF::sensors::CameraPinholeRadTan> camera(new SDF::sensors::CameraPinholeRadTan());
  camera->name = cameraPath.filename().string();
  camera->transform = SDF::Transform(cameraConfig["T_BS"]["data"].as<std::vector<float>>());

  camera->comment = cameraConfig["comment"].as<std::string>();
  camera->rate = cameraConfig["rate_hz"].as<float>();
  camera->width = cameraConfig["resolution"][0].as<uint32_t>();
  camera->height = cameraConfig["resolution"][1].as<uint32_t>();
  std::vector<float> intrinsics = cameraConfig["intrinsics"].as<std::vector<float>>();
  camera->fx = intrinsics[0];
  camera->fy = intrinsics[1];
  camera->cx = intrinsics[2];
  camera->cy = intrinsics[3];
  std::vector<float> distortion = cameraConfig["distortion_coefficients"].as<std::vector<float>>();
  camera->k1 = distortion[0];
  camera->k2 = distortion[1];
  camera->p1 = distortion[2];
  camera->p2 = distortion[3];

  camera->lazyLoad = true;

  for (std::filesystem::path imagePath : std::filesystem::directory_iterator(cameraPath / "data"))
  {
    std::shared_ptr<SDF::sensors::CameraPinholeRadTan::Data> cameraData = std::make_shared<SDF::sensors::CameraPinholeRadTan::Data>();
    cameraData->timestamp = std::stoull(imagePath.stem());
    cameraData->imagePath = imagePath;
    camera->data.push_back(cameraData);
  }

  sdf->addSensor(camera);
}

void processIMU(std::filesystem::path imuPath, YAML::Node imuConfig, std::shared_ptr<SDF::SDF> sdf)
{
  std::shared_ptr<SDF::sensors::IMU6DOFAllan> imu(new SDF::sensors::IMU6DOFAllan());
  imu->name = imuPath.filename().string();
  imu->transform = SDF::Transform(imuConfig["T_BS"]["data"].as<std::vector<float>>());

  imu->comment = imuConfig["comment"].as<std::string>();
  imu->rate = imuConfig["rate_hz"].as<float>();
  imu->gyroscope_noise_density = imuConfig["gyroscope_noise_density"].as<float>();
  imu->gyroscope_random_walk = imuConfig["gyroscope_random_walk"].as<float>();
  imu->accelerometer_noise_density = imuConfig["accelerometer_noise_density"].as<float>();
  imu->accelerometer_random_walk = imuConfig["accelerometer_random_walk"].as<float>();

  imu->lazyLoad = false;

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
    std::shared_ptr<SDF::sensors::IMU6DOFAllan::Data> imuData = std::make_shared<SDF::sensors::IMU6DOFAllan::Data>();
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
    imu->data.push_back(imuData);

    std::cout << imuData->timestamp << ", " << imuData->ax << ", " << imuData->ay << ", " << imuData->az << ", " << imuData->wx << ", " << imuData->wy << ", " << imuData->wz << std::endl;
  }
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

  // TODO: Reenable, just for testing
  // std::cout << "Do you wish to continue? [Y/n] " << std::ends;

  // char response;
  // std::cin.get(response);
  // if (response != 'Y' && response != 'y' && response != '\n')
  // {
  //   exit(0);
  // }

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