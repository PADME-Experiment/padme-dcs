#include "DrvCaenHV.h"   //in c file
#include <caenlib/CAENHVWrapper.h>
#include<iostream>

  DrvCaenHV_except&
DrvCaenHV_except::CAENWrapperRetStatus(int caenhandler,int retstatus, const std::string& add)
{ std::string a(CAENHV_GetError(caenhandler));
  std::string str("CAENHVWrapper returned error ("+std::to_string(retstatus)+") : '" + a + "'");
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
DrvCaenHV::ComInit()
{
  CAENHVRESULT ret;
  CAENHV_SYSTEM_TYPE_t sys_type = (CAENHV_SYSTEM_TYPE_t) SY4527; // 0: SY1527, 2: SY4527
  int link_type = LINKTYPE_TCPIP;
  ret = CAENHV_InitSystem(sys_type, link_type, (void*)fIPAddress.c_str(), fUsername.c_str(), fPassword.c_str(), &fCaenCrateHandle);
  if(ret != CAENHV_OK){
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret,
        "IP = "+fIPAddress+"  user = "+fUsername+"  pass = "+fPassword);
  }
}

  void
DrvCaenHV::ComDeinit()
{
  int ret = CAENHV_DeinitSystem(fCaenCrateHandle);
  if(ret != CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
}

  void
DrvCaenHV::GetCrateMap()
{
  ushort nrslots, *nrchlist, *sernumlist;
  char *modellist,*descrlist;
  unsigned char *firmwaremin,*firmawaremax;

  int ret = CAENHV_GetCrateMap(fCaenCrateHandle,
      &nrslots,            //ushort *NrOfSlot,
      &nrchlist,           //ushort **NrofChList,
      &modellist,          //char **ModelList,
      &descrlist,          //char **DescriptionList,
      &sernumlist,         //ushort **SerNumList,
      &firmwaremin,        //uchar **FmwRelMinList,
      &firmawaremax);      //uchar **FmwRelMaxList);

  if(ret != CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
  std::vector<std::string>modelVec;
  std::vector<std::string>descrVec;
  ConvCharListVector(nrslots,modellist,modelVec);
  ConvCharListVector(nrslots,descrlist,descrVec);

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

  int ret=CAENHV_GetExecCommList(fCaenCrateHandle,&numcom,&comnamelist);
  if(ret!=CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
  std::vector<std::string> list;
  ConvCharListVector(numcom,comnamelist,list);
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

  int ret=CAENHV_GetSysPropList(fCaenCrateHandle,&numcom,&comnamelist);
  if(ret!=CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);

  std::vector<std::string> list;
  ConvCharListVector(numcom,comnamelist,list);

  int len=0;
  for(int i=0;i<numcom;++i){
    std::cout<<list[i]<<"   ";
  } std::cout<<std::endl;

  CAENHV_Free(comnamelist);

}


  void
DrvCaenHV::AssertInit()
{
  ComInit();
}




//TODO: tazi funkciya da otide v utl ili fwk
  void
DrvCaenHV::ConvCharListVector(unsigned short n,const char* l,std::vector<std::string>&v)
{
  v.clear();
  int len=0;
  for(int i=0;i<n;++i){
    std::string tmp(&l[len]);
    len+=tmp.size()+1;
    v.push_back(tmp);
  }
}



  void
DrvCaenHV::GetSysProp(const std::string&cmd, void* res)
{
  int ret=CAENHV_GetSysProp(fCaenCrateHandle,cmd.c_str(),res);
  if(ret!=CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
  //Sessions   ModelName   SwRelease   GenSignCfg   FrontPanIn   FrontPanOut   ResFlagCfg   ResFlag   HvPwSM   HVFanStat   ClkFreq   HVClkConf   IPAddr   IPNetMsk   IPGw   PWCurrent   OutputLevel   SymbolicName   CmdQueueStatus   CPULoad   MemoryStatus   HVFanSpeed   PWFanStat   PWVoltage   DummyReg   CMDExecMode
}

  void
DrvCaenHV::GetSysProp_ModelName()
{
  char tmp[80];
  GetSysProp("ModelName",tmp);
  fModelName<<tmp;
  INFO(tmp);
  INFO(fModelName.GetValue());
}



