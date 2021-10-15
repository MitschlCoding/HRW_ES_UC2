#include "LED.h"

sc2::LED::LED(char pinNum): ODevice(1){
  sc2::Pin ledPin = sc2::Pin(pinNum, true);
  this->setPin(0,ledPin);
}

void sc2::LED::deviceInit(){
  this->getPin(0)->pinInit();
  this->getPin(0)->state = true;
}

void sc2::LED::deviceUpdate(){
  this->getPin(0)->pinUpdate();
}


void sc2::LED::turnOn(bool _state){
  this->getPin(0)->state = _state;
}
