#include "IOController.h"

uc2::IOController::IOController(){}

void uc2::IOController::addODevice(ODevice* _device){
  oDevices.push_back(_device);
}

uc2::ODevice* uc2::IOController::getODevice(int _id){
  for(auto i: oDevices){
    if(i->id == _id){
      return i;
    }
  }
}

void uc2::IOController::removeODevice(int _id){
  for(auto i: oDevices){
    if(i->id == _id){
      oDevices.remove(i);
      break;
    }
  }
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
