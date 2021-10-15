#include "LED.h"

uc2::LED::LED(char pinNum): ODevice(1){
  uc2::Pin ledPin = uc2::Pin(pinNum, true);
  this->setPin(0,ledPin);
}

void uc2::LED::deviceInit(){
  this->getPin(0)->pinInit();
  this->getPin(0)->state = true;
}

void uc2::LED::deviceUpdate(){
  this->getPin(0)->pinUpdate();
}


void uc2::LED::turnOn(bool _state){
  this->getPin(0)->state = _state;
}
