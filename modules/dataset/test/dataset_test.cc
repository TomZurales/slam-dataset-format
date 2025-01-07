#include <catch2/catch_test_macros.hpp>

#include "sdf/dataset.h"

TEST_CASE("Dataset headers can be parsed from files", "[dataset]")
{
  SDF::Dataset dataset = SDF::Dataset::Load("modules/dataset/test/data/dataset_test.csv");
}