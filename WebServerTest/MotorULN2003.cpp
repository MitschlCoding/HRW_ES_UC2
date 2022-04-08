#include "MotorULN2003.h"

uc2::MotorULN2003::MotorULN2003(int _id, int _pin1, int _pin2, int _pin3, int _pin4) : ODevice(_id, 0){
  stepper.connectToPins(_pin1, _pin2, _pin3, _pin4);
  this->type = "MotorULN2003";
}

void uc2::MotorULN2003::deviceInit(){
  stepper.setSpeedInStepsPerSecond(1024/2);
  stepper.setAccelerationInStepsPerSecondPerSecond(1024/2);
}

void uc2::MotorULN2003::deviceUpdate(){
  if(steps != 0){
    stepper.moveRelativeInSteps(steps);
    steps = 0;
  }
}
