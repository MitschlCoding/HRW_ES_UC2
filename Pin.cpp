#include "Pin.h"

sc2::Pin::Pin(int _pinNum, bool _output) : pinNum(_pinNum), isOutput(_output), state(false){}

sc2::Pin::Pin(){}

void sc2::Pin::pinInit(){
  if(isOutput){
    pinMode(pinNum, OUTPUT);
  } else {
    pinMode(pinNum, INPUT);
  }
}

void sc2::Pin::pinUpdate(){
  if(state){
    digitalWrite(pinNum, HIGH);
  } else {
    digitalWrite(pinNum, LOW);
  }
}
