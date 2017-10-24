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
  INFO(std::to_string(inset.size())+" lines to be proc");
  std::string group;
  std::set<std::string>subset;
  while (utl::ExtractFirstPrefix(inset,subset,group)){
    for(auto it=subset.begin();it!=subset.end();++it){
      if(group.size()==0)
        throw fwk::Exception_tobefixed("empty group");
      INFO("calls group "+group);
      Get(group)->SetLocalParams(subset);
    }
  }
}

  void
VDeviceBase::SetUpdate(const std::string&what,unsigned int interval)
{
  if(what=="*"){
    update_par_t upd;
    upd.cmd=what;
    upd.func=std::bind(&VDeviceBase::UpdateAllLocalParams,this);
    upd.interval=interval;
    fScheduledUpdates.insert(std::multimap<time_t,update_par_t>::value_type(0,upd));
  }else throw fwk::Exception_tobefixed("Unknown update commad '"+what+"'");
}

  void
VDeviceBase::Update()
{
  INFO(GetName());
  auto it=fScheduledUpdates.begin();
  while(it!=fScheduledUpdates.end()&&std::difftime(std::time(nullptr),it->first)>=0){
    const auto upd=it->second; //copy not reference
    INFO(GetName()+"    Inside while "+upd.cmd+"  "+std::to_string(upd.interval));
    upd.func();
    it=fScheduledUpdates.erase(it);
    fScheduledUpdates.insert(std::multimap<time_t,update_par_t>::value_type(std::time(nullptr)+upd.interval, upd));
  }

  for(auto it=fDevs. begin();it!=fDevs. end();++it){
    it->second.get()->Update();
  }
}


void
VDeviceBase::GetInfoAll(std::stringstream&ss)
{
  for(auto it=fDevs. begin();it!=fDevs. end();++it){
    it->second.get()->GetInfoAll(ss);
  }
  GetInfoAllLocal(ss);
}


  void
VDeviceDriver::OnCycle()
{
  INFO(GetName());
  std::this_thread::sleep_for(std::chrono::seconds(1));
  Update();
  OnCycleLocal();
}
