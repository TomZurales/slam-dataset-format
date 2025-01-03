#include <catch2/catch_test_macros.hpp>

#include "sdf/plugins/camera_pinhole_radtan.h"

TEST_CASE("properties can be serialized and deserialized", "[camera_pinhole_radtan]")
{
  SDF::sensors::CameraPinholeRadTan camera;
}