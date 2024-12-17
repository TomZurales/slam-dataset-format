#pragma once

#include <cstdint>
#include <ostream>
#include <string>
#include <sstream>

#include "sdf/blob.h"

namespace SDF
{
  class Header
  {
  public:
    uint32_t magic;
    uint8_t version_major;
    uint8_t version_minor;
    uint32_t num_frames;
    uint32_t num_sensors;
    uint32_t num_data;
    uint32_t size;

    Header() : magic(0x51A3DA7A), version_major(0), version_minor(1), num_frames(0),
               num_sensors(0), num_data(0), size(0)
    {
    }
    ~Header() = default;

    std::shared_ptr<Blob> toBlob()
    {
      std::shared_ptr<Blob> blob = std::make_shared<Blob>(22);
      *blob << magic;
      *blob << version_major;
      *blob << version_minor;
      *blob << num_frames;
      *blob << num_sensors;
      *blob << num_data;
      *blob << size;
      std::cout << "Header size: " << blob->size << std::endl;
      return blob;
    }

    static Header fromStream(std::ifstream &stream)
    {
      Header header;
      stream.read(reinterpret_cast<char *>(&header.magic), sizeof(header.magic));
      stream.read(reinterpret_cast<char *>(&header.version_major), sizeof(header.version_major));
      stream.read(reinterpret_cast<char *>(&header.version_minor), sizeof(header.version_minor));
      stream.read(reinterpret_cast<char *>(&header.num_frames), sizeof(header.num_frames));
      stream.read(reinterpret_cast<char *>(&header.num_sensors), sizeof(header.num_sensors));
      stream.read(reinterpret_cast<char *>(&header.num_data), sizeof(header.num_data));
      stream.read(reinterpret_cast<char *>(&header.size), sizeof(header.size));
      return header;
    }

    std::string to_string()
    {
      std::stringstream ss;
      ss << "Magic: 0x" << std::hex << std::uppercase << magic << std::endl;
      ss << "SDF Version: " << static_cast<uint32_t>(version_major) << "." << static_cast<uint32_t>(version_minor) << std::endl;
      ss << "Number of frames: " << num_frames << std::endl;
      ss << "Number of sensors: " << num_sensors << std::endl;
      ss << "Number of data: " << num_data << std::endl;
      ss << "Size: " << size << std::endl;
      return ss.str();
    }
  };
}