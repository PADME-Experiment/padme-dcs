#include "VDeviceDriver.h"   //in c file
#include "fwk/utlCommaDashListToVector.h"


std::shared_ptr<VDeviceBase>
VDeviceBase::AddDevice(const std::string& lab, std::shared_ptr<VDeviceBase>ptr)
{
  // TODO: should also set the global name of the device PADME/xxx/yyy/zzz
  // TODO: should check if the device existed before

  fDevs[lab]=ptr;
  return ptr;
}

  bool
VDeviceBase::GetNext(ElemIter& it)
{
  std::stringstream ss;
  ss<<&(*it);
  INFO(ss.str());
  if(it==static_cast<ElemIter>(nullptr))
    it=fDevs.begin();
  else ++it;
  if(it==fDevs.end()){
    it=static_cast<ElemIter>(nullptr);
    return false;
  }
  return true;

}

  void
VDeviceBase::SetParams(std::set<std::string>inset/**< [in] should be copy not reference!*/)
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
