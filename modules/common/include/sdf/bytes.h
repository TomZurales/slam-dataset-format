#pragma once

#include <cstdint>
#include <cstring>
#include <memory>
#include <fstream>
#include <vector>
#include <filesystem>

namespace SDF
{
  // Forward declaration
  class Serializable;

  class Bytes
  {
  protected:
    std::vector<uint8_t> bytes;
    size_t position = 0;

  public:
    Bytes() = default;
    ~Bytes() = default;

    void add_raw(const void *data, size_t size)
    {
      bytes.insert(bytes.end(), reinterpret_cast<const uint8_t *>(&size), reinterpret_cast<const uint8_t *>(&size) + sizeof(size_t));
      bytes.insert(bytes.end(), reinterpret_cast<const uint8_t *>(data), reinterpret_cast<const uint8_t *>(data) + size);
      position = bytes.size();
    }

    template <typename T>
    void add(const T &value)
    {
      static_assert(std::is_trivially_copyable<T>::value, "Type must be trivially copyable");
      const uint8_t *begin = reinterpret_cast<const uint8_t *>(&value);
      const uint8_t *end = begin + sizeof(T);
      bytes.insert(bytes.end(), begin, end);
      position = bytes.size();
    }

    template <typename T>
    T get(size_t offset)
    {
      static_assert(std::is_trivially_copyable<T>::value, "Type must be trivially copyable");
      T value;
      std::memcpy(&value, bytes.data() + offset, sizeof(T));
      position = offset + sizeof(T);
      return value;
    }

    template <typename T>
    T get()
    {
      static_assert(std::is_trivially_copyable<T>::value, "Type must be trivially copyable");
      T value;
      std::memcpy(&value, bytes.data() + position, sizeof(T));
      position = position + sizeof(T);
      return value;
    }

    void *get_raw(size_t offset)
    {
      size_t size = *reinterpret_cast<const size_t *>(bytes.data() + offset);
      void *data = malloc(size);
      std::memcpy(data, bytes.data() + offset + sizeof(size_t), size);
      position = offset + sizeof(size_t) + size;
      return data;
    }

    void *get_raw()
    {
      size_t size = *reinterpret_cast<const size_t *>(bytes.data() + position);
      void *data = malloc(size);
      std::memcpy(data, bytes.data() + position + sizeof(size_t), size);
      position = position + sizeof(size_t) + size;
      return data;
    }

    std::vector<uint8_t> get_raw_vec()
    {
      std::vector<uint8_t> data;
      size_t size = *reinterpret_cast<const size_t *>(bytes.data() + position);
      data.resize(size);
      std::memcpy(data.data(), bytes.data() + position + sizeof(size_t), size);
      position = position + sizeof(size_t) + size;
      return data;
    }

    void resetPosition()
    {
      position = 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const Bytes &bytes)
    {
      os.write(reinterpret_cast<const char *>(bytes.bytes.size()), sizeof(bytes.bytes.size()));
      os.write(reinterpret_cast<const char *>(bytes.bytes.data()), bytes.bytes.size());
      return os;
    }

    static Bytes fromFile(std::filesystem::path path)
    {
      std::ifstream file(path, std::ios::binary);
      if (!file.is_open())
      {
        throw std::runtime_error("Could not open file");
      }
      Bytes bytes = Bytes();
      file.seekg(0, std::ios::end);
      size_t size = file.tellg();
      file.seekg(0, std::ios::beg);
      bytes.bytes.resize(size);
      file.read(reinterpret_cast<char *>(bytes.bytes.data()), size);
      return bytes;
    }

    static Bytes fromStream(std::istream &stream)
    {
      Bytes bytes;
      size_t size;
      stream.read(reinterpret_cast<char *>(&size), sizeof(size));
      bytes.bytes.resize(size);
      stream.read(reinterpret_cast<char *>(bytes.bytes.data()), size);
      return bytes;
    }
  };
}