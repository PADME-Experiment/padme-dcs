#include "VDeviceDriver.h"   //in c file
#include "fwk/utlCommaDashListToVector.h"


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

  void
VDeviceDriver::SetParams(std::set<std::string>inset/**< [in] should be copy not reference!*/)
{
  std::string group;
  std::set<std::string>subset;
  while (utl::ExtractFirstPrefix(inset,subset,group)){
    for(auto it=subset.begin();it!=subset.end();++it){
      INFO("calls group "+group);
      Get(group)->SetParams(subset);
    }
  }
}
