#include "MotorDRV8825.h"

uc2::MotorDRV8825::MotorDRV8825(int _id, int _pin1, int _pin2) : ODevice(_id, 2){
  uc2::Pin pin1 = uc2::Pin(_pin1, true);
  uc2::Pin pin2 = uc2::Pin(_pin2, true);
  this->setPin(0, pin1);
  this->setPin(1, pin2);
  this->type = "MotorDRV8825";
}

void uc2::MotorDRV8825::deviceInit(){
  this->getPin(0)->pinInit();
  this->getPin(1)->pinInit();
}

void uc2::MotorDRV8825::deviceUpdate(){
    if(this->steps > 0){
      this->getPin(0)->state = true;
      this->getPin(0)->pinUpdate();
      // Spin the stepper motor by steps
      for (int i = 0; i < steps; i++) {
        // These four lines result in 1 step:
        this->getPin(1)->state = true;
        this->getPin(1)->pinUpdate();
        delayMicroseconds(1000);
        this->getPin(1)->state = false;
        this->getPin(1)->pinUpdate();
        delayMicroseconds(1000);
      }
    }
    if(this->steps < 0){
      this->getPin(0)->state = false;
      this->getPin(0)->pinUpdate();
      // Spin the stepper motor by steps
      for (int i = 0; i < -steps; i++) {
        // These four lines result in 1 step:
        this->getPin(1)->state = true;
        this->getPin(1)->pinUpdate();
        delayMicroseconds(1000);
        this->getPin(1)->state = false;
        this->getPin(1)->pinUpdate();
        delayMicroseconds(1000);
      }
    }
    this->steps = 0;
}
