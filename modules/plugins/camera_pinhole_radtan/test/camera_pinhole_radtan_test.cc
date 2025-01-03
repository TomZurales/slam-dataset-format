#include <catch2/catch_test_macros.hpp>

#include "sdf/plugins/camera_pinhole_radtan.h"
#include "sdf/test/helpers.h"
#include "sdf/bytes.h"

SDF::sensors::CameraPinholeRadTan generateRandomCamera(int n_data)
{
  SDF::sensors::CameraPinholeRadTan camera;

  auto props = camera.getProps();

  props->notes = randomString(randomInt(1, 100));
  props->rate = randomFloat(1.0, 120.0);
  props->width = randomInt(1, 100);
  props->height = randomInt(1, 100);
  props->fx = randomFloat(1.0, 10000.0);
  props->fy = randomFloat(1.0, 10000.0);
  props->cx = randomFloat(1.0, 10000.0);
  props->cy = randomFloat(1.0, 10000.0);
  props->k1 = randomFloat(0.0, 1.0);
  props->k2 = randomFloat(0.0, 1.0);
  props->p1 = randomFloat(0.0, 1.0);
  props->p2 = randomFloat(0.0, 1.0);
  props->k3 = randomFloat(0.0, 1.0);
  props->imageChannels = randomInt(1, 4);

  for (int i = 0; i < n_data; i++)
  {
    auto newData = std::make_shared<SDF::sensors::CameraPinholeRadTanData>();
    newData->timestamp = i;
    newData->image = cv::Mat(camera.getProps()->height, camera.getProps()->width, CV_8UC3, cv::Scalar(randomFloat(0.0, 255.0), randomFloat(0.0, 255.0), randomFloat(0.0, 255.0)));
    camera.addData(newData);
  }

  return camera;
}

TEST_CASE("Instances of camera_pinhole_radtan can be serialized and desearilized", "[camera_pinhole_radtan]")
{
  SDF::sensors::CameraPinholeRadTan camera = generateRandomCamera(10);
  SECTION("Properties can be serialized and deserialized from Bytes objects")
  {
    auto cameraPropsBytes = camera.getProps()->toBytes();

    auto deserializedProps = SDF::sensors::CameraPinholeRadTanProps::fromBytes(cameraPropsBytes);

    REQUIRE(*camera.getProps() == deserializedProps);
  }
  SECTION("Data can be serialized and deserialized from Bytes objects")
  {
    for (auto data : camera.getData())
    {
      auto cameraDataBytes = data->toBytes();

      auto deserializedData = SDF::sensors::CameraPinholeRadTanData::fromBytes(cameraDataBytes);

      REQUIRE(*data == deserializedData);
    }
  }
  SECTION("Properties can be serialized and desearialized from a file")
  {
    auto cameraPropsBytes = camera.getProps()->toBytes();
    std::ofstream out_file("/tmp/camera_pinhole_radtan_props", std::ios::binary);
    out_file << cameraPropsBytes;
    out_file.close();

    auto deserializedPropsBytes = SDF::Bytes::fromFile("/tmp/camera_pinhole_radtan_props");
    auto deserializeProps = SDF::sensors::CameraPinholeRadTanProps::fromBytes(deserializedPropsBytes);

    REQUIRE(*camera.getProps() == deserializeProps);
  }
  SECTION("Data can be serialized and desearialized from a file")
  {
    auto cameraData = camera.getData();
    for (auto data : cameraData)
    {
      auto cameraDataBytes = data->toBytes();
      std::ofstream out_file("/tmp/camera_pinhole_radtan_data", std::ios::binary);
      out_file << cameraDataBytes;
      out_file.close();

      auto deserializedDataBytes = SDF::Bytes::fromFile("/tmp/camera_pinhole_radtan_data");
      auto deserializeData = SDF::sensors::CameraPinholeRadTanData::fromBytes(deserializedDataBytes);

      REQUIRE(*data == deserializeData);
    }
  }
}