#include <catch2/catch_test_macros.hpp>

#include "sdf/plugins/imu_6dof_allan.h"
#include "sdf/test/helpers.h"
#include "sdf/bytes.h"

SDF::sensors::Imu6dofAllan generateRandomIMU(int n_data)
{
  SDF::sensors::Imu6dofAllan imu;

  auto props = imu.getProps();

  props->name = randomString(randomInt(1, 100));
  props->notes = randomString(randomInt(1, 100));
  props->rate = randomFloat(1.0, 120.0);
  props->accelerometer_noise_density = randomFloat(0.0, 1.0);
  props->gyroscope_noise_density = randomFloat(0.0, 1.0);
  props->accelerometer_random_walk = randomFloat(0.0, 1.0);
  props->gyroscope_random_walk = randomFloat(0.0, 1.0);

  for (int i = 0; i < n_data; i++)
  {
    auto newData = std::make_shared<SDF::sensors::Imu6dofAllanData>();
    newData->timestamp = i;
    newData->ax = randomFloat(-10.0, 10.0);
    newData->ay = randomFloat(-10.0, 10.0);
    newData->az = randomFloat(-10.0, 10.0);
    newData->wx = randomFloat(-10.0, 10.0);
    newData->wy = randomFloat(-10.0, 10.0);
    newData->wz = randomFloat(-10.0, 10.0);
    imu.addData(newData);
  }

  return imu;
}

TEST_CASE("Instances of imu_6dof_allan can be serialized and desearilized", "[imu_6dof_allan]")
{
  SDF::sensors::Imu6dofAllan imu = generateRandomIMU(10);
  SECTION("Properties can be serialized and deserialized from Bytes objects")
  {
    auto imuPropsBytes = imu.getProps()->toBytes();

    auto deserializedProps = SDF::sensors::Imu6dofAllanProps::fromBytes(imuPropsBytes);

    REQUIRE(*imu.getProps() == deserializedProps);
  }
  SECTION("Data can be serialized and deserialized from Bytes objects")
  {
    for (auto data : imu.getData())
    {
      auto imuDataBytes = data->toBytes();

      auto deserializedData = SDF::sensors::Imu6dofAllanData::fromBytes(imuDataBytes);

      REQUIRE(*data == deserializedData);
    }
  }
  SECTION("Properties can be serialized and desearialized from a file")
  {
    auto imuPropsBytes = imu.getProps()->toBytes();
    std::ofstream out_file("/tmp/imu_6dof_allan_props", std::ios::binary);
    out_file << imuPropsBytes;
    out_file.close();

    auto deserializedPropsBytes = SDF::Bytes::fromFile("/tmp/imu_6dof_allan_props");
    auto deserializeProps = SDF::sensors::Imu6dofAllanProps::fromBytes(deserializedPropsBytes);

    REQUIRE(*imu.getProps() == deserializeProps);
  }
  SECTION("Data can be serialized and desearialized from a file")
  {
    auto imuData = imu.getData();
    for (auto data : imuData)
    {
      auto imuDataBytes = data->toBytes();
      std::ofstream out_file("/tmp/imu_6dof_allan_data", std::ios::binary);
      out_file << imuDataBytes;
      out_file.close();

      auto deserializedDataBytes = SDF::Bytes::fromFile("/tmp/imu_6dof_allan_data");
      auto deserializeData = SDF::sensors::Imu6dofAllanData::fromBytes(deserializedDataBytes);

      REQUIRE(*data == deserializeData);
    }
  }
}