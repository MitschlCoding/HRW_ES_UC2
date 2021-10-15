#pragma once
#include "ODevice.h"
#include "Pin.h"
#include <Arduino.h>

//an output device, that turns an LED permanently on
namespace uc2{
  class LED: public ODevice{
    public:
      LED();
      LED(char _pinNum);
      //turns the LED on or of
      void turnOn(bool _state);
      //initialises the LED and set the given pins to be output pins
      void deviceInit();
      //turn the pin state to on and calls pin.update()
      void deviceUpdate();
  };
}
