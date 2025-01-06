#include "sdf/plugins/imu_6dof_allan.h"

SDF::Bytes SDF::sensors::Imu6dofAllanProps::toBytes()
{
  Bytes bytes = Bytes();
  bytes.add_raw(notes.data(), notes.size());
  bytes.add(rate);
  bytes.add(accelerometer_noise_density);
  bytes.add(gyroscope_noise_density);
  bytes.add(accelerometer_random_walk);
  bytes.add(gyroscope_random_walk);
  return bytes;
}

SDF::sensors::Imu6dofAllanProps SDF::sensors::Imu6dofAllanProps::fromBytes(SDF::Bytes bytes)
{
  bytes.resetPosition();
  Imu6dofAllanProps props = Imu6dofAllanProps();
  props.notes = std::string(static_cast<char *>(bytes.get_raw()));
  props.rate = bytes.get<float>();
  props.accelerometer_noise_density = bytes.get<float>();
  props.gyroscope_noise_density = bytes.get<float>();
  props.accelerometer_random_walk = bytes.get<float>();
  props.gyroscope_random_walk = bytes.get<float>();

  return props;
}

SDF::Bytes SDF::sensors::Imu6dofAllanData::toBytes()
{
  Bytes bytes = Bytes();
  bytes.add(timestamp);
  bytes.add<float>(ax);
  bytes.add<float>(ay);
  bytes.add<float>(az);
  bytes.add<float>(wx);
  bytes.add<float>(wy);
  bytes.add<float>(wz);
  return bytes;
}

SDF::sensors::Imu6dofAllanData SDF::sensors::Imu6dofAllanData::fromBytes(SDF::Bytes bytes)
{
  bytes.resetPosition();
  Imu6dofAllanData data = Imu6dofAllanData();
  data.timestamp = bytes.get<uint64_t>();
  data.ax = bytes.get<float>();
  data.ay = bytes.get<float>();
  data.az = bytes.get<float>();
  data.wx = bytes.get<float>();
  data.wy = bytes.get<float>();
  data.wz = bytes.get<float>();
  return data;
}