#include "Motor.h"

uc2::Motor::Motor(int _id, int _pin1, int _pin2, int _pin3, int _pin4) : ODevice(_id, 0){
  stepper.connectToPins(_pin1, _pin2, _pin3, _pin4);
}

void uc2::Motor::deviceInit(){
  stepper.setSpeedInStepsPerSecond(1024/2);
  stepper.setAccelerationInStepsPerSecondPerSecond(1024/2);
}

void uc2::Motor::deviceUpdate(){
  if(steps != 0){
    stepper.moveRelativeInSteps(steps);
    steps = 0;
  }
}
