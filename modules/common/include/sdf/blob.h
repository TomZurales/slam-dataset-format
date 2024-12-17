#pragma once

#include <cstdint>
#include <cstring>
#include <memory>

namespace SDF
{
  class Blob
  {
  public:
    const uint32_t size;
    uint32_t offset;
    std::shared_ptr<uint8_t> data;

    Blob(uint32_t size) : size(size), offset(0), data(new uint8_t[size])
    {
    }
    ~Blob() = default;

    template <typename T>
    Blob &operator<<(const T &value)
    {
      static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
      if (offset + sizeof(T) > size)
      {
        throw std::overflow_error("Blob overflow");
      }
      std::memcpy(data.get() + offset, &value, sizeof(T));
      offset += sizeof(T);
      return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Blob &blob)
    {
      os.write(reinterpret_cast<const char *>(blob.data.get()), blob.size);
      return os;
    }

    template <typename T>
    Blob &operator>>(T &value)
    {
      static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
      if (offset + sizeof(T) > size)
      {
        throw std::overflow_error("Blob overflow");
      }
      std::memcpy(&value, data.get() + offset, sizeof(T));
      offset += sizeof(T);
      return *this;
    }
  };
}