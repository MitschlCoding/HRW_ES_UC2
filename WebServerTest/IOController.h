#pragma once
#include "ODevice.h"
#include <list>


//This controller handles all I/O Devices and handels the adding/removing of devices and their updating
//has a list of devices that can be added to
namespace uc2{
  class IOController{
    public:
      IOController();
      //adds a device to the output device list
      void addODevice(ODevice* _oDevice);
      //calls all initialisation functions from devices in oDevices
      void controllerInit();
      //calls all update functions from devices in oDevices
      void controllerUpdate();
      std::list<ODevice*> oDevices;
  };
}
