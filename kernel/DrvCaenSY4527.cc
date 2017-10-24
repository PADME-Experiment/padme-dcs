#include "DrvCaenSY4527.h"   //in c file
#include"fwk/utlCommaDashListToVector.h"
#include <caenlib/CAENHVWrapper.h>



VCaenHVMainFrame::VCaenHVMainFrame(const std::string& s, VDeviceBase*d):
  fCaenCrateHandle      (static_cast<DrvCaenHV*>(d)->GetCaenCrateHandle()),
  fCaenCrateHandle_mutex(static_cast<DrvCaenHV*>(d)->GetCaenCrateHandle_mutex()),
  VDeviceBase(s,d)
{}



  void
VCaenHVMainFrame::UpdateAllLocalParams()
{
  GetSysProp_Sessions      ();
  GetSysProp_ModelName     ();
  GetSysProp_SwRelease     ();
  GetSysProp_GenSignCfg    ();
  GetSysProp_FrontPanIn    ();
  GetSysProp_FrontPanOut   ();
  GetSysProp_ResFlagCfg    ();
  GetSysProp_HvPwSM        ();
  GetSysProp_HVFanStat     ();
  GetSysProp_ClkFreq       ();
  GetSysProp_HVClkConf     ();
  GetSysProp_IPAddr        ();
  GetSysProp_IPNetMsk      ();
  GetSysProp_IPGw          ();
  GetSysProp_PWCurrent     ();
  GetSysProp_OutputLevel   ();
  GetSysProp_SymbolicName  ();
  GetSysProp_CmdQueueStatus();
  GetSysProp_CPULoad       ();
  GetSysProp_MemoryStatus  ();
}





  void
VCaenHVMainFrame::GetCrateMap()
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
      <<"modellist   ["<<i<<"]'"<<modelVec         [i] <<"'"<<std::endl
      <<"descrlist   ["<<i<<"]'"<<descrVec         [i] <<"'"<<std::endl
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
VCaenHVMainFrame::GetExecCommList() ///Get list of possible 
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
VCaenHVMainFrame::GetSysProp(const std::string&cmd, void* res)
{
  int ret;
  std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
  ret=CAENHV_GetSysProp(fCaenCrateHandle,cmd.c_str(),res);
  if(ret!=CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
}

  void
VCaenHVMainFrame::GetSysPropList() ///Get list of possible 
{
  ushort numcom;
  char*comnamelist;
  int ret;
  {
    std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
    ret=CAENHV_GetSysPropList(fCaenCrateHandle,&numcom,&comnamelist);
    if(ret!=CAENHV_OK)
      DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
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
VCaenHVMainFrame::GetInfoAllLocal(std::stringstream& ss)
{
  ss<<GetName()<<"   Sessions       "<<fSessions      .GetVal()<<"  "<<fSessions      .GetAge()<<std::endl;
  ss<<GetName()<<"   ModelName      "<<fModelName     .GetVal()<<"  "<<fModelName     .GetAge()<<std::endl;
  ss<<GetName()<<"   SwRelease      "<<fSwRelease     .GetVal()<<"  "<<fSwRelease     .GetAge()<<std::endl;
  ss<<GetName()<<"   GenSignCfg     "<<fGenSignCfg    .GetVal()<<"  "<<fGenSignCfg    .GetAge()<<std::endl;
  ss<<GetName()<<"   FrontPanIn     "<<fFrontPanIn    .GetVal()<<"  "<<fFrontPanIn    .GetAge()<<std::endl;
  ss<<GetName()<<"   FrontPanOut    "<<fFrontPanOut   .GetVal()<<"  "<<fFrontPanOut   .GetAge()<<std::endl;
  ss<<GetName()<<"   ResFlagCfg     "<<fResFlagCfg    .GetVal()<<"  "<<fResFlagCfg    .GetAge()<<std::endl;
  ss<<GetName()<<"   HvPwSM         "<<fHvPwSM        .GetVal()<<"  "<<fHvPwSM        .GetAge()<<std::endl;
  ss<<GetName()<<"   HVFanStat      "<<fHVFanStat     .GetVal()<<"  "<<fHVFanStat     .GetAge()<<std::endl;
  ss<<GetName()<<"   ClkFreq        "<<fClkFreq       .GetVal()<<"  "<<fClkFreq       .GetAge()<<std::endl;
  ss<<GetName()<<"   HVClkConf      "<<fHVClkConf     .GetVal()<<"  "<<fHVClkConf     .GetAge()<<std::endl;
  ss<<GetName()<<"   IPAddr         "<<fIPAddr        .GetVal()<<"  "<<fIPAddr        .GetAge()<<std::endl;
  ss<<GetName()<<"   IPNetMsk       "<<fIPNetMsk      .GetVal()<<"  "<<fIPNetMsk      .GetAge()<<std::endl;
  ss<<GetName()<<"   IPGw           "<<fIPGw          .GetVal()<<"  "<<fIPGw          .GetAge()<<std::endl;
  ss<<GetName()<<"   PWCurrent      "<<fPWCurrent     .GetVal()<<"  "<<fPWCurrent     .GetAge()<<std::endl;
  ss<<GetName()<<"   OutputLevel    "<<fOutputLevel   .GetVal()<<"  "<<fOutputLevel   .GetAge()<<std::endl;
  ss<<GetName()<<"   SymbolicName   "<<fSymbolicName  .GetVal()<<"  "<<fSymbolicName  .GetAge()<<std::endl;
  ss<<GetName()<<"   CmdQueueStatus "<<fCmdQueueStatus.GetVal()<<"  "<<fCmdQueueStatus.GetAge()<<std::endl;
  ss<<GetName()<<"   CPULoad        "<<fCPULoad       .GetVal()<<"  "<<fCPULoad       .GetAge()<<std::endl;
  ss<<GetName()<<"   MemoryStatus   "<<fMemoryStatus  .GetVal()<<"  "<<fMemoryStatus  .GetAge()<<std::endl;
}












void DrvCaenSY4527::GetSysProp_Sessions      (){char tmp[500];GetSysProp("Sessions"       , tmp);fSessions      .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_ModelName     (){char tmp[80] ;GetSysProp("ModelName"      , tmp);fModelName     .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_SwRelease     (){char tmp[80] ;GetSysProp("SwRelease"      , tmp);fSwRelease     .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_GenSignCfg    (){uint16_t tmp ;GetSysProp("GenSignCfg"     ,&tmp);fGenSignCfg    .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_FrontPanIn    (){uint16_t tmp ;GetSysProp("FrontPanIn"     ,&tmp);fFrontPanIn    .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_FrontPanOut   (){uint16_t tmp ;GetSysProp("FrontPanOut"    ,&tmp);fFrontPanOut   .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_ResFlagCfg    (){uint16_t tmp ;GetSysProp("ResFlagCfg"     ,&tmp);fResFlagCfg    .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_HvPwSM        (){char tmp[80] ;GetSysProp("HvPwSM"         , tmp);fHvPwSM        .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_HVFanStat     (){char tmp[80] ;GetSysProp("HVFanStat"      , tmp);fHVFanStat     .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_ClkFreq       (){uint16_t tmp ;GetSysProp("ClkFreq"        ,&tmp);fClkFreq       .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_HVClkConf     (){char tmp[80] ;GetSysProp("HVClkConf"      , tmp);fHVClkConf     .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_IPAddr        (){char tmp[80] ;GetSysProp("IPAddr"         , tmp);fIPAddr        .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_IPNetMsk      (){char tmp[80] ;GetSysProp("IPNetMsk"       , tmp);fIPNetMsk      .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_IPGw          (){char tmp[80] ;GetSysProp("IPGw"           , tmp);fIPGw          .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_PWCurrent     (){char tmp[80] ;GetSysProp("PWCurrent"      , tmp);fPWCurrent     .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_OutputLevel   (){uint16_t tmp ;GetSysProp("OutputLevel"    ,&tmp);fOutputLevel   .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_SymbolicName  (){char tmp[80] ;GetSysProp("SymbolicName"   , tmp);fSymbolicName  .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_CmdQueueStatus(){uint16_t tmp ;GetSysProp("CmdQueueStatus" ,&tmp);fCmdQueueStatus.SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_CPULoad       (){char tmp[80] ;GetSysProp("CPULoad"        , tmp);fCPULoad       .SetVal(tmp);}
void DrvCaenSY4527::GetSysProp_MemoryStatus  (){char tmp[80] ;GetSysProp("MemoryStatus"   , tmp);fMemoryStatus  .SetVal(tmp);}
