#include <catch2/catch_test_macros.hpp>

#include "sdf/plugins/camera_pinhole_radtan.h"

TEST_CASE("properties can be serialized and deserialized", "[camera_pinhole_radtan]")
{
  SDF::sensors::CameraPinholeRadTan camera;

  auto props = std::static_pointer_cast<SDF::sensors::CameraPinholeRadTanProps>(camera.getProps());
  props->imageChannels = 3;
  props->dataType = 0;
  props->notes = "This is a test";

  props->toBytes();
}