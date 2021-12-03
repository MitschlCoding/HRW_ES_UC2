#pragma once
#include "Odevice.h"

namespace uc2{
  class MotorDRV8825: public ODevice{
    public:
      MotorDRV8825(int _id, int _pin1, int _pin2);
      void deviceInit();
      void deviceUpdate();
      int steps = 0;
  };
}
