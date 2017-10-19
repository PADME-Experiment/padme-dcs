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
VDeviceBase::SetUpdate(const std::string&what,unsigned int interval)
{
  size_t slashp=what.find_first_of("/");
  if(what=="*"){
  }
  if(slashp!=std::string::npos){
    auto group=what.substr(0,slashp);
    auto newwhat=what.substr(slashp+1);
    Get(group).get()->SetUpdate(newwhat,interval);
  }
  if(slashp==std::string::npos||what=="*"){
    SetLocalUpdate(what,interval);
  }
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
VDeviceBase::UpdateAll()
{
  auto it=fScheduledUpdates.begin();
  while(it!=fScheduledUpdates.end()&&std::difftime(std::time(nullptr),it->first)>=0){
    const auto upd=it->second; //copy not reference
    UpdateAllLocal(upd.cmd);
    fScheduledUpdates.insert(std::multimap<time_t,update_par_t>::value_type(std::time(nullptr)+upd.interval, upd));
  }

  for(auto it=fDevs. begin();it!=fDevs. end();++it){it->second.get()->UpdateAll();
  }
}

  void
VDeviceBase::SetLocalUpdate(const std::string&what,unsigned int interval)
{
  if(what!="*"){
    fwk::Exception_tobefixed("command "+what+" is not supported");
  }
  update_par_t upd;
  upd.cmd=what;
  upd.interval=interval;
  fScheduledUpdates.insert(std::multimap<time_t,update_par_t>::value_type(0,upd));
}
