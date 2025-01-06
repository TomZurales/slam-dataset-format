#include "sdf/plugins/imu_6dof_allan.h"

// std::vector<std::shared_ptr<SDF::Sensor::Data>> SDF::sensors::Imu6dofAllan::getData() const
// {
//   return data;
// }

// void SDF::sensors::Imu6dofAllan::show() const
// {
//   std::cout << "Imu6dofAllan: " << name << std::endl;

//   std::cout << "Transform: ";
//   transform.show();
//   std::cout << "Comment: " << notes << std::endl;
//   std::cout << "Rate: " << rate << " Hz" << std::endl;
//   std::cout << "Gyroscope Noise Density: " << gyroscope_noise_density << " rad/s/sqrt(Hz)" << std::endl;
//   std::cout << "Gyroscope Random Walk: " << gyroscope_random_walk << " rad/s/sqrt(s)" << std::endl;
//   std::cout << "Accelerometer Noise Density: " << accelerometer_noise_density << " m/s^2/sqrt(Hz)" << std::endl;
//   std::cout << "Accelerometer Random Walk: " << accelerometer_random_walk << " m/s^2/sqrt(s)" << std::endl;
// }

// SDF::Bytes SDF::sensors::Imu6dofAllan::toBytes()
// {
//   Bytes bytes = Bytes();
//   bytes.add(name);
//   bytes.add(transform);

//   bytes.add(notes);
//   bytes.add(rate);

//   bytes.add(gyroscope_noise_density);
//   bytes.add(gyroscope_random_walk);
//   bytes.add(accelerometer_noise_density);
//   bytes.add(accelerometer_random_walk);

//   return bytes;
// }