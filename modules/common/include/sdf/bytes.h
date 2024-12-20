#pragma once

#include <cstdint>
#include <cstring>
#include <memory>

// Forward declaration of the Serializable class
namespace SDF
{
  class Serializable;
}

namespace SDF
{
  class Bytes
  {
  protected:
    std::vector<uint8_t> bytes;

  public:
    Bytes() = default;
    ~Bytes() = default;

    void add(std::string value)
    {
      const uint8_t *begin = reinterpret_cast<const uint8_t *>(value.data());
      const uint8_t *end = begin + value.size();
      add(value.size());
      bytes.insert(bytes.end(), begin, end);
    }

    template <typename T>
    void add(const T &value)
    {
      static_assert(std::is_trivially_copyable<T>::value || std::is_base_of<SDF::Serializable, T>::value, "T must be trivially copyable");
      const uint8_t *begin = reinterpret_cast<const uint8_t *>(&value);
      const uint8_t *end = begin + sizeof(T);
      bytes.insert(bytes.end(), begin, end);
    }

    friend std::ostream &operator<<(std::ostream &os, const Bytes &bytes)
    {
      os.write(reinterpret_cast<const char *>(bytes.bytes.data()), bytes.bytes.size());
      return os;
    }
  };
}