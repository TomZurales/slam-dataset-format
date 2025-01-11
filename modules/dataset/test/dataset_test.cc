#include <catch2/catch_test_macros.hpp>
#include <fstream>

#include "sdf/dataset.h"

TEST_CASE("Datasets can be loaded from SDF files", "[dataset]")
{
  std::ofstream datasetFile("/tmp/dataset_test.sdf", std::ios::binary);
  uint32_t header = 0x51A3DA7A;
  datasetFile.write(reinterpret_cast<const char *>(&header), 4);
  uint32_t numPlugins = 0;
  datasetFile.close();

  SDF::Dataset dataset = SDF::Dataset::Load("/tmp/dataset_test.sdf");

  REQUIRE(dataset.getStatus() == 0);
}

TEST_CASE("Datasets with incorrect checksums fail to load", "[dataset]")
{
  std::ofstream datasetFile("/tmp/dataset_test.sdf", std::ios::binary);
  uint32_t header = 0x51A3DA7B;
  datasetFile.write(reinterpret_cast<const char *>(&header), 4);
  datasetFile.close();

  SDF::Dataset dataset = SDF::Dataset::Load("/tmp/dataset_test.sdf");

  REQUIRE(dataset.getStatus() != 0);
}

TEST_CASE("Plugins can be loaded by datasets", "[dataset]")
{
  SDF::Dataset dataset;
  dataset.addPlugin(SDF::Plugin("test_plugin"));
  dataset.write("/tmp/dataset_test.sdf");

  SDF::Dataset loadedDataset = SDF::Dataset::Load("/tmp/dataset_test.sdf");
  REQUIRE(loadedDataset.getStatus() == 0);
  REQUIRE(loadedDataset.getPlugins().size() == 1);
  REQUIRE(loadedDataset.getPlugins()[0].getName() == "test_plugin");
}