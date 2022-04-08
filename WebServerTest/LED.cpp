#include "LED.h"

uc2::LED::LED(int _id, char _pinNum): ODevice(_id, 1){
  uc2::Pin ledPin = uc2::Pin(_pinNum, true);
  this->setPin(0,ledPin);
  this->type = "LED";
}

void uc2::LED::deviceInit(){
  this->getPin(0)->pinInit();
  this->getPin(0)->state = true;
}

void uc2::LED::deviceUpdate(){
  this->getPin(0)->pinUpdate();
}


void uc2::LED::turnOnOff(){
  this->getPin(0)->state = !this->getPin(0)->state;
}
