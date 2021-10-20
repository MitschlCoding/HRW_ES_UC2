#pragma once
#include "Odevice.h"
#include <TinyStepper_28BYJ_48.h>

namespace uc2{
  class Motor: public ODevice{
    public:
      Motor(int _id, int _pin1, int _pin2, int _pin3, int _pin4);
      void deviceInit();
      void deviceUpdate();
      int steps = 0;
    private:
      TinyStepper_28BYJ_48 stepper;
  };
}
