#include "Motor.h"

uc2::Motor::Motor(int _pin1, int _pin2, int _pin3, int _pin4) : ODevice(0){
  stepper.connectToPins(_pin1, _pin2, _pin3, _pin4);
}

void uc2::Motor::deviceInit(){
  stepper.setSpeedInStepsPerSecond(256);
  stepper.setAccelerationInStepsPerSecondPerSecond(512);
}

void uc2::Motor::deviceUpdate(){
  if(steps != 0){
    stepper.moveRelativeInSteps(steps);
    steps = 0;
  }
}
