#include "IOController.h"

sc2::IOController::IOController(){}

void sc2::IOController::addODevice(ODevice* _device){
  oDevices.push_back(_device);
}

void sc2::IOController::controllerInit(){
  for(auto i : oDevices){
    i->deviceInit();
  }
}

void sc2::IOController::controllerUpdate(){
  for(auto i : oDevices){
    i->deviceUpdate();
  }
}
