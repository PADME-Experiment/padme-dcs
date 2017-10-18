#include "DrvCaenHV.h"   //in c file
#include"fwk/utlCommaDashListToVector.h"
#include <caenlib/CAENHVWrapper.h>
#include<iostream>

  DrvCaenHV_except&
DrvCaenHV_except::CAENWrapperRetStatus(int caenhandler,int retstatus, const std::string& add)
{ std::string a(CAENHV_GetError(caenhandler));
std::string error=(
retstatus==0     ? "Command wrapper correctly executed"                                            :
retstatus==1     ? "Error of operatived system"                                                    :
retstatus==2     ? "Write error in communication channel"                                          :
retstatus==3     ? "Read error in communication channel"                                           :
retstatus==4     ? "Time out in server communication"                                              :
retstatus==5     ? "Command Front End application is down"                                         :
retstatus==6     ? "Communication with system not yet connected by a Login command"                :
retstatus==7     ? "Communication with a not present board/slot"                                   :
retstatus==8     ? "Communication with RS232 not yet implemented"                                  :
retstatus==9     ? "User memory not sufficient"                                                    :
retstatus==10    ? "Value out of range"                                                            :
retstatus==11    ? "Execute command not yet implemented"                                           :
retstatus==12    ? "Get Property not yet implemented"                                              :
retstatus==13    ? "Set Property not yet implemented"                                              :
retstatus==14    ? "Property not found"                                                            :
retstatus==15    ? "Execute command not found"                                                     :
retstatus==16    ? "No System property"                                                            :
retstatus==17    ? "No get property"                                                               :
retstatus==18    ? "No set property"                                                               :
retstatus==19    ? "No execute command"                                                            :
retstatus==20    ? "Device configuration changed"                                                  :
retstatus==21    ? "Property of param not found"                                                   :
retstatus==22    ? "Param not found"                                                               :
retstatus==23    ? "No data present"                                                               :
retstatus==24    ? "Device already open"                                                           :
retstatus==25    ? "To Many devices opened"                                                        :
retstatus==26    ? "Function Parameter not valid"                                                  :
retstatus==27    ? "Function not available for the connected device"                               :
retstatus==0x1001? "Device already connected"                                                      :
retstatus==0x1002? "Device not connected"                                                          :
retstatus==0x1003? "Operating system error"                                                        :
retstatus==0x1004? "Login failed"                                                                  :
retstatus==0x1005? "Logout failed"                                                                 :
retstatus==0x1006? "Link type not supported"                                                       :
retstatus==0x1007? "Login failed for username/password ( SY4527 / SY5527 )"                        :
"Unknown");


  std::string str("CAENHVWrapper returned error ("+std::to_string(retstatus)+") : '" + a + "'  "+error);
  if(add.size()>0)str+="   "+add;

  switch (retstatus){
    case CAENHV_SYSERR               : throw DrvCaenHV_except::Except_SYSERR               (str) ;break;
    case CAENHV_WRITEERR             : throw DrvCaenHV_except::Except_WRITEERR             (str) ;break;
    case CAENHV_READERR              : throw DrvCaenHV_except::Except_READERR              (str) ;break;
    case CAENHV_TIMEERR              : throw DrvCaenHV_except::Except_TIMEERR              (str) ;break;
    case CAENHV_DOWN                 : throw DrvCaenHV_except::Except_DOWN                 (str) ;break;
    case CAENHV_NOTPRES              : throw DrvCaenHV_except::Except_NOTPRES              (str) ;break;
    case CAENHV_SLOTNOTPRES          : throw DrvCaenHV_except::Except_SLOTNOTPRES          (str) ;break;
    case CAENHV_NOSERIAL             : throw DrvCaenHV_except::Except_NOSERIAL             (str) ;break;
    case CAENHV_MEMORYFAULT          : throw DrvCaenHV_except::Except_MEMORYFAULT          (str) ;break;
    case CAENHV_OUTOFRANGE           : throw DrvCaenHV_except::Except_OUTOFRANGE           (str) ;break;
    case CAENHV_EXECCOMNOTIMPL       : throw DrvCaenHV_except::Except_EXECCOMNOTIMPL       (str) ;break;
    case CAENHV_GETPROPNOTIMPL       : throw DrvCaenHV_except::Except_GETPROPNOTIMPL       (str) ;break;
    case CAENHV_SETPROPNOTIMPL       : throw DrvCaenHV_except::Except_SETPROPNOTIMPL       (str) ;break;
    case CAENHV_PROPNOTFOUND         : throw DrvCaenHV_except::Except_PROPNOTFOUND         (str) ;break;
    case CAENHV_EXECNOTFOUND         : throw DrvCaenHV_except::Except_EXECNOTFOUND         (str) ;break;
    case CAENHV_NOTSYSPROP           : throw DrvCaenHV_except::Except_NOTSYSPROP           (str) ;break;
    case CAENHV_NOTGETPROP           : throw DrvCaenHV_except::Except_NOTGETPROP           (str) ;break;
    case CAENHV_NOTSETPROP           : throw DrvCaenHV_except::Except_NOTSETPROP           (str) ;break;
    case CAENHV_NOTEXECOMM           : throw DrvCaenHV_except::Except_NOTEXECOMM           (str) ;break;
    case CAENHV_SYSCONFCHANGE        : throw DrvCaenHV_except::Except_SYSCONFCHANGE        (str) ;break;
    case CAENHV_PARAMPROPNOTFOUND    : throw DrvCaenHV_except::Except_PARAMPROPNOTFOUND    (str) ;break;
    case CAENHV_PARAMNOTFOUND        : throw DrvCaenHV_except::Except_PARAMNOTFOUND        (str) ;break;
    case CAENHV_NODATA               : throw DrvCaenHV_except::Except_NODATA               (str) ;break;
    case CAENHV_DEVALREADYOPEN       : throw DrvCaenHV_except::Except_DEVALREADYOPEN       (str) ;break;
    case CAENHV_TOOMANYDEVICEOPEN    : throw DrvCaenHV_except::Except_TOOMANYDEVICEOPEN    (str) ;break;
    case CAENHV_INVALIDPARAMETER     : throw DrvCaenHV_except::Except_INVALIDPARAMETER     (str) ;break;
    case CAENHV_FUNCTIONNOTAVAILABLE : throw DrvCaenHV_except::Except_FUNCTIONNOTAVAILABLE (str) ;break;
    case CAENHV_SOCKETERROR          : throw DrvCaenHV_except::Except_SOCKETERROR          (str) ;break;
    case CAENHV_COMMUNICATIONERROR   : throw DrvCaenHV_except::Except_COMMUNICATIONERROR   (str) ;break;
    case CAENHV_NOTYETIMPLEMENTED    : throw DrvCaenHV_except::Except_NOTYETIMPLEMENTED    (str) ;break;
    case CAENHV_CONNECTED            : throw DrvCaenHV_except::Except_CONNECTED            (str) ;break;
    case CAENHV_NOTCONNECTED         : throw DrvCaenHV_except::Except_NOTCONNECTED         (str) ;break;
    case CAENHV_OS                   : throw DrvCaenHV_except::Except_OS                   (str) ;break;
    case CAENHV_LOGINFAILED          : throw DrvCaenHV_except::Except_LOGINFAILED          (str) ;break;
    case CAENHV_LOGOUTFAILED         : throw DrvCaenHV_except::Except_LOGOUTFAILED         (str) ;break;
    case CAENHV_LINKNOTSUPPORTED     : throw DrvCaenHV_except::Except_LINKNOTSUPPORTED     (str) ;break;
    case CAENHV_USERPASSFAILED       : throw DrvCaenHV_except::Except_USERPASSFAILED       (str) ;break;
  }
}










  void
DrvCaenHV::SetParams(std::set<std::string>inset/**< [in] should be copy not reference!*/)
{
  std::string group;
  std::set<std::string>subset;
  while (utl::ExtractFirstPrefix(inset,subset,group)){
    for(auto it=subset.begin();it!=subset.end();++it){
      INFO("DrvCaenHV calls group "+group);
      std::dynamic_pointer_cast<VCaenHVBoard>(Get(group))->SetParams(subset);
    }
  }
}




  int
DrvCaenHV::ComInit()
{
  CAENHVRESULT ret;
  int handle;
  CAENHV_SYSTEM_TYPE_t sys_type = (CAENHV_SYSTEM_TYPE_t) SY4527; // 0: SY1527, 2: SY4527
  int link_type = LINKTYPE_TCPIP;
  ret = CAENHV_InitSystem(sys_type, link_type, (void*)fIPAddress.c_str(), fUsername.c_str(), fPassword.c_str(), &handle);
  if(ret != CAENHV_OK){
    DrvCaenHV_except::CAENWrapperRetStatus(handle,ret,
        "IP = "+fIPAddress+"  user = "+fUsername+"  pass = "+fPassword);
  }
  return handle;
}

  void
DrvCaenHV::ComDeinit(int handle)
{
  int ret = CAENHV_DeinitSystem(handle);
  if(ret != CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(handle,ret);
}

  void
DrvCaenHV::GetCrateMap()
{
  ushort nrslots, *nrchlist, *sernumlist;
  char *modellist,*descrlist;
  unsigned char *firmwaremin,*firmawaremax;

  int ret;
  {
    std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
    ret = CAENHV_GetCrateMap(fCaenCrateHandle,
      &nrslots,            //ushort *NrOfSlot,
      &nrchlist,           //ushort **NrofChList,
      &modellist,          //char **ModelList,
      &descrlist,          //char **DescriptionList,
      &sernumlist,         //ushort **SerNumList,
      &firmwaremin,        //uchar **FmwRelMinList,
      &firmawaremax);      //uchar **FmwRelMaxList);
  }

  if(ret != CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
  std::vector<std::string>modelVec;
  std::vector<std::string>descrVec;
  utl::ConvCharListVector(nrslots,modellist,modelVec);
  utl::ConvCharListVector(nrslots,descrlist,descrVec);

  for(int i=0;i<nrslots;++i){
    std::cout
      <<"nrchlist    ["<<i<<"]'"<<nrchlist         [i] <<"'"<<std::endl
      <<"modellist   ["<<i<<"]'"<<modelVec        [i] <<"'"<<std::endl
      <<"descrlist   ["<<i<<"]'"<<descrVec        [i] <<"'"<<std::endl
      <<"sernumlist  ["<<i<<"]'"<<sernumlist       [i] <<"'"<<std::endl
      <<"firmwaremin ["<<i<<"]'"<<int(firmwaremin  [i])<<"'"<<std::endl
      <<"firmawaremax["<<i<<"]'"<<int(firmawaremax [i])<<"'"<<std::endl
      <<std::endl;
  }

  std::cerr<<"bef del "<<__FILE__<<__LINE__<<__func__<<std::endl;
  CAENHV_Free(nrchlist    );/// must be dealocated by the user
  CAENHV_Free(modellist   );/// must be dealocated by the user
  CAENHV_Free(descrlist   );/// must be dealocated by the user
  CAENHV_Free(sernumlist  );/// must be dealocated by the user
  CAENHV_Free(firmwaremin );/// must be dealocated by the user
  CAENHV_Free(firmawaremax);/// must be dealocated by the user
}


  void
DrvCaenHV::GetExecCommList() ///Get list of possible 
{
  ushort numcom;
  char*comnamelist;

  int ret;
  { std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
    ret=CAENHV_GetExecCommList(fCaenCrateHandle,&numcom,&comnamelist);
    if(ret!=CAENHV_OK) DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
  }

  std::vector<std::string> list;
  utl::ConvCharListVector(numcom,comnamelist,list);
  int len=0;
  for(int i=0;i<numcom;++i){
    std::cout<<list[i]<<"   ";
  } std::cout<<std::endl;

  CAENHV_Free(comnamelist);

}


  void
DrvCaenHV::GetSysPropList() ///Get list of possible 
{
  ushort numcom;
  char*comnamelist;

  int ret;
  { std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
    ret=CAENHV_GetSysPropList(fCaenCrateHandle,&numcom,&comnamelist);}
  if(ret!=CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);

  std::vector<std::string> list;
  utl::ConvCharListVector(numcom,comnamelist,list);

  int len=0;
  for(int i=0;i<numcom;++i){
    std::cout<<list[i]<<"   ";
  } std::cout<<std::endl;

  CAENHV_Free(comnamelist);

}


  void
DrvCaenHV::AssertInit()
{
  INFO("DrvCaenHV::AssertInit()");
  //#warning CAEN ComInit
  fCaenCrateHandle=ComInit();
  AssertInitAllOwned();
}
  void
DrvCaenHV::Finalize()
{
  this->VDeviceBase::Finalize();
  //#warning CAEN ComDeinit
  ComDeinit(fCaenCrateHandle );
  JoinThread();
}


void
DrvCaenHV::OnCycle(){
  std::this_thread::sleep_for(std::chrono::seconds(3));DebugUpdate();
  VDeviceDriver::ElemIter devit;
  devit=static_cast<VDeviceDriver::ElemIter>(nullptr);
  while(GetNext(devit)){devit->second->DebugUpdate();}
}

  void
DrvCaenHV::GetSysProp(const std::string&cmd, void* res)
{
  int ret;
  {
    std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
    ret=CAENHV_GetSysProp(fCaenCrateHandle,cmd.c_str(),res);
  }
  if(ret!=CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
}


void DrvCaenHV::GetSysProp_Sessions      (){char tmp[500];GetSysProp("Sessions"       , tmp);fSessions      <<tmp;}
void DrvCaenHV::GetSysProp_ModelName     (){char tmp[80];GetSysProp("ModelName"      , tmp);fModelName     <<tmp;}
void DrvCaenHV::GetSysProp_SwRelease     (){char tmp[80];GetSysProp("SwRelease"      , tmp);fSwRelease     <<tmp;}
void DrvCaenHV::GetSysProp_GenSignCfg    (){uint16_t tmp;GetSysProp("GenSignCfg"     ,&tmp);fGenSignCfg    <<tmp;}
void DrvCaenHV::GetSysProp_FrontPanIn    (){uint16_t tmp;GetSysProp("FrontPanIn"     ,&tmp);fFrontPanIn    <<tmp;}
void DrvCaenHV::GetSysProp_FrontPanOut   (){uint16_t tmp;GetSysProp("FrontPanOut"    ,&tmp);fFrontPanOut   <<tmp;}
void DrvCaenHV::GetSysProp_ResFlagCfg    (){uint16_t tmp;GetSysProp("ResFlagCfg"     ,&tmp);fResFlagCfg    <<tmp;}
void DrvCaenHV::GetSysProp_HvPwSM        (){char tmp[80];GetSysProp("HvPwSM"         , tmp);fHvPwSM        <<tmp;}
void DrvCaenHV::GetSysProp_HVFanStat     (){char tmp[80];GetSysProp("HVFanStat"      , tmp);fHVFanStat     <<tmp;}
void DrvCaenHV::GetSysProp_ClkFreq       (){uint16_t tmp;GetSysProp("ClkFreq"        ,&tmp);fClkFreq       <<tmp;}
void DrvCaenHV::GetSysProp_HVClkConf     (){char tmp[80];GetSysProp("HVClkConf"      , tmp);fHVClkConf     <<tmp;}
void DrvCaenHV::GetSysProp_IPAddr        (){char tmp[80];GetSysProp("IPAddr"         , tmp);fIPAddr        <<tmp;}
void DrvCaenHV::GetSysProp_IPNetMsk      (){char tmp[80];GetSysProp("IPNetMsk"       , tmp);fIPNetMsk      <<tmp;}
void DrvCaenHV::GetSysProp_IPGw          (){char tmp[80];GetSysProp("IPGw"           , tmp);fIPGw          <<tmp;}
void DrvCaenHV::GetSysProp_PWCurrent     (){char tmp[80];GetSysProp("PWCurrent"      , tmp);fPWCurrent     <<tmp;}
void DrvCaenHV::GetSysProp_OutputLevel   (){uint16_t tmp;GetSysProp("OutputLevel"    ,&tmp);fOutputLevel   <<tmp;}
void DrvCaenHV::GetSysProp_SymbolicName  (){char tmp[80];GetSysProp("SymbolicName"   , tmp);fSymbolicName  <<tmp;}
void DrvCaenHV::GetSysProp_CmdQueueStatus(){uint16_t tmp;GetSysProp("CmdQueueStatus" ,&tmp);fCmdQueueStatus<<tmp;}
void DrvCaenHV::GetSysProp_CPULoad       (){char tmp[80];GetSysProp("CPULoad"        , tmp);fCPULoad       <<tmp;}
void DrvCaenHV::GetSysProp_MemoryStatus  (){char tmp[80];GetSysProp("MemoryStatus"   , tmp);fMemoryStatus  <<tmp;}
