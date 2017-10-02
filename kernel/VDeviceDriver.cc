#include "VDeviceDriver.h"   //in c file


  void
VDeviceDriver::AddDevice(const std::string& lab, std::shared_ptr<VDeviceDriver>ptr)
{
  fAllDevs[lab]=ptr;
}

