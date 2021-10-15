#pragma once
#include "Pin.h"

//represents a ODevice

namespace uc2{
  class ODevice {
    public:
      //numOfPins is the number of pins the device needs
      ODevice(char _numOfPins);
      ~ODevice();
      //initialisation and update of Device that is defined in the child classes
      //init is supposed to run only once, when the device is added to the list of devices or after the post request is made
      virtual void deviceInit() = 0;
      //update is supposed to run every time the state of the pins or the device itself changes
      virtual void deviceUpdate() = 0;
      //sets the pin at pinIndex to a pin
      void setPin(char _pinIndex, Pin _pin);
      //return the pin at pinIndex, if the index is out of bounce, the last item in array is returned
      Pin* getPin(char _pinIndex);
    private:
      char numOfPins;
      Pin* pins;
  };
}
