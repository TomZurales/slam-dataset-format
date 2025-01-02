#include <catch2/catch_test_macros.hpp>

#include "sdf/plugins/camera_pinhole_radtan.h"

TEST_CASE("properties can be serialized and deserialized", "[camera_pinhole_radtan]")
{
  SDF::sensors::CameraPinholeRadTan camera;

  // SECTION("notes can be set and retrieved")
  // {
  //   camera.notes = "This is a camera";
  //   REQUIRE(camera.notes == "This is a camera");
  // }

  // SECTION("rate can be set and retrieved")
  // {
  //   camera.rate = 30.0;
  //   REQUIRE(camera.rate == 30.0);
  // }
}