#include "VDeviceDriver.h"   //in c file


std::shared_ptr<VDeviceDriver>
VDeviceDriver::AddDevice(const std::string& lab, std::shared_ptr<VDeviceDriver>ptr)
{
  fAllDevs[lab]=ptr;
  return ptr;
}

