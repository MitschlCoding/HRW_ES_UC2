#include "IOController.h"

uc2::IOController::IOController(){}

void uc2::IOController::addODevice(ODevice* _device){
  oDevices.push_back(_device);
}

void uc2::IOController::controllerInit(){
  for(auto i : oDevices){
    i->deviceInit();
  }
}

void uc2::IOController::controllerUpdate(){
  for(auto i : oDevices){
    i->deviceUpdate();
  }
}
