#pragma once
#include <Arduino.h>

//represents an pin for the ESP
namespace uc2{
  class Pin{
    public:
      //constructs a Pin with a pinNum(number of IO on ESP) and output(weither the pin is an output)
      Pin(int _pinNum, bool _output);
      Pin();
      //Init is supposed to run once, when the pin is added to an device
      void pinInit();
      //update is supposed to be run every tim the device is updated
      void pinUpdate();
      //weither the pin is an output pin (true) or an input pin (false)
      bool isOutput;
      //the IOPin number on the ESP
      int pinNum;
      //true for HIGH, false for LOW
      bool state;
  };
}
