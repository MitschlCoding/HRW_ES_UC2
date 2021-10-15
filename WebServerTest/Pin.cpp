#include "Pin.h"

uc2::Pin::Pin(int _pinNum, bool _output) : pinNum(_pinNum), isOutput(_output), state(false){}

uc2::Pin::Pin(){}

void uc2::Pin::pinInit(){
  if(isOutput){
    pinMode(pinNum, OUTPUT);
  } else {
    pinMode(pinNum, INPUT);
  }
}

void uc2::Pin::pinUpdate(){
  if(state){
    digitalWrite(pinNum, HIGH);
  } else {
    digitalWrite(pinNum, LOW);
  }
}
