#include <iostream>
#include <filesystem>

#include "sdf/sdf.h"

int main(int argc, char **argv)
{
  if (argc < 2 || argc > 3)
  {
    std::cerr << "Usage: EuRoC_to_SDF <dataset_path> [output_name]" << std::endl;
    exit(1);
  }

  std::filesystem::path input_path(argv[1]);
  input_path = std::filesystem::canonical(input_path);

  if (!std::filesystem::is_directory(input_path / "mav0"))
  {
    std::cerr << "No EuRoC dataset could be found at "
              << std::filesystem::canonical(input_path).string()
              << " . Please check the path and try again" << std::endl;
    exit(1);
  }

  std::filesystem::path output_path(".");
  output_path = std::filesystem::canonical(output_path);

  if (argc == 3)
  {
    if (std::filesystem::path(argv[2]).extension() == ".sdf")
    {
      output_path = output_path / argv[2];
    }
    else
    {
      output_path = output_path / (std::string(argv[2]) + ".sdf");
    }
  }
  else
  {
    output_path = output_path / (input_path.filename().string() + ".sdf");
  }

  if (std::filesystem::exists(output_path))
  {
    std::cerr << "Output file " << output_path.string() << " already exists. Please delete or specify a different output name." << std::endl;
    exit(1);
  }

  std::cout << "EuRoC to SDF Converter" << std::endl;
  std::cout << "Input: " << input_path.string() << std::endl;
  std::cout << "Output: " << output_path.string() << std::endl;
  std::cout << "Do you wish to continue? [Y/n]" << std::endl;
  return 0;
}