#include "sdf/plugins/imu_6dof_allan.h"

std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::IMU6DOFAllan::getData() const
{
  return data;
}

void SDF::sensors::IMU6DOFAllan::show() const
{
  std::cout << "IMU6DOFAllan: " << name << std::endl;

  std::cout << "Transform: ";
  transform.show();
  std::cout << "Comment: " << notes << std::endl;
  std::cout << "Rate: " << rate << " Hz" << std::endl;
  std::cout << "Gyroscope Noise Density: " << gyroscope_noise_density << " rad/s/sqrt(Hz)" << std::endl;
  std::cout << "Gyroscope Random Walk: " << gyroscope_random_walk << " rad/s/sqrt(s)" << std::endl;
  std::cout << "Accelerometer Noise Density: " << accelerometer_noise_density << " m/s^2/sqrt(Hz)" << std::endl;
  std::cout << "Accelerometer Random Walk: " << accelerometer_random_walk << " m/s^2/sqrt(s)" << std::endl;
}

SDF::Blob SDF::sensors::IMU6DOFAllan::serialize()
{
  Blob blob = Blob(24);
  return blob;
}