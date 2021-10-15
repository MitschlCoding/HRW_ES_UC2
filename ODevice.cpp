#include "ODevice.h"

sc2::ODevice::ODevice(char _numOfPins) : numOfPins(_numOfPins){
  pins = new Pin[numOfPins];
}

sc2::ODevice::~ODevice(){
  delete pins;
}

void sc2::ODevice::setPin(char _pinIndex, Pin _pin){
  if(_pinIndex >= numOfPins){
    return;
  }
  pins[_pinIndex] = _pin;
}

sc2::Pin* sc2::ODevice::getPin(char _pinIndex){
  if(_pinIndex >= numOfPins){
    return &pins[numOfPins];
  }
  return &pins[_pinIndex];
}
