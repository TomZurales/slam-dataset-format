#include "sdf/serializable.h"

namespace SDF
{
  namespace Sensor_
  {
    class Data : public Serializable
    {
    public:
      virtual ~Data() = default;
    };
  }
}