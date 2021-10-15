#include "ODevice.h"

uc2::ODevice::ODevice(char _numOfPins) : numOfPins(_numOfPins){
  pins = new Pin[numOfPins];
}

uc2::ODevice::~ODevice(){
  delete pins;
}

void uc2::ODevice::setPin(char _pinIndex, Pin _pin){
  if(_pinIndex >= numOfPins){
    return;
  }
  pins[_pinIndex] = _pin;
}

uc2::Pin* uc2::ODevice::getPin(char _pinIndex){
  if(_pinIndex >= numOfPins){
    return &pins[numOfPins];
  }
  return &pins[_pinIndex];
}
