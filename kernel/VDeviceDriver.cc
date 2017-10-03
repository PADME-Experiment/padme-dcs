#include "VDeviceDriver.h"   //in c file


std::shared_ptr<VDeviceDriver>
VDeviceDriver::AddDevice(const std::string& lab, std::shared_ptr<VDeviceDriver>ptr)
{
  fAllDevs[lab]=ptr;
  return ptr;
}
  bool 
VDeviceDriver::GetNext(ElemIter& it)
{
  std::stringstream ss;
  ss<<&(*it);
  INFO(ss.str());
  if(it==static_cast<ElemIter>(nullptr))
    it=fAllDevs.begin();
  else ++it;
  if(it==fAllDevs.end()){
    it=static_cast<ElemIter>(nullptr);
    return false;
  }
  return true;

}
