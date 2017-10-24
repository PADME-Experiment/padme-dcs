#ifndef  _DCS_kernel_DrvCaenSY4527_h_
#define  _DCS_kernel_DrvCaenSY4527_h_ 1
#include "DrvCaenSY4527.h"   //in c file
#include "DrvCaenHV.h"

class VCaenHVMainFrame :public VDeviceBase{
  public:
    VCaenHVMainFrame(const std::string& s, VDeviceBase*d);
      void AssertInit(){AssertMainFrameType();}
  private:
    const int &fCaenCrateHandle;
    std::mutex&fCaenCrateHandle_mutex;
  public:
    //TODO Setters for all parameters
    void GetCrateMap();
    void GetExecCommList();
    void GetSysPropList();
  protected:
    void GetSysProp(const std::string&cmd, void* res);
  protected:
    virtual void AssertMainFrameType()=0;
    private:
    void SetLocalParams(std::set<std::string>){}
    void UpdateAllLocalParams();
  public:
    //TODO Setters for all parameters
    virtual void GetSysProp_Sessions      ()=0;
    virtual void GetSysProp_ModelName     ()=0;
    virtual void GetSysProp_SwRelease     ()=0;
    virtual void GetSysProp_GenSignCfg    ()=0;
    virtual void GetSysProp_FrontPanIn    ()=0;
    virtual void GetSysProp_FrontPanOut   ()=0;
    virtual void GetSysProp_ResFlagCfg    ()=0;
    virtual void GetSysProp_HvPwSM        ()=0;
    virtual void GetSysProp_HVFanStat     ()=0;
    virtual void GetSysProp_ClkFreq       ()=0;
    virtual void GetSysProp_HVClkConf     ()=0;
    virtual void GetSysProp_IPAddr        ()=0;
    virtual void GetSysProp_IPNetMsk      ()=0;
    virtual void GetSysProp_IPGw          ()=0;
    virtual void GetSysProp_PWCurrent     ()=0;
    virtual void GetSysProp_OutputLevel   ()=0;
    virtual void GetSysProp_SymbolicName  ()=0;
    virtual void GetSysProp_CmdQueueStatus()=0;
    virtual void GetSysProp_CPULoad       ()=0;
    virtual void GetSysProp_MemoryStatus  ()=0;
  protected: // values
    CaenHVCrateValue<std::string> fSessions        ;
    CaenHVCrateValue<std::string> fModelName       ;
    CaenHVCrateValue<std::string> fSwRelease       ;
    CaenHVCrateValue<uint16_t   > fGenSignCfg      ;
    CaenHVCrateValue<uint16_t   > fFrontPanIn      ;
    CaenHVCrateValue<uint16_t   > fFrontPanOut     ;
    CaenHVCrateValue<uint16_t   > fResFlagCfg      ;
    CaenHVCrateValue<std::string> fHvPwSM          ;
    CaenHVCrateValue<std::string> fHVFanStat       ;
    CaenHVCrateValue<uint16_t   > fClkFreq         ;
    CaenHVCrateValue<std::string> fHVClkConf       ;
    CaenHVCrateValue<std::string> fIPAddr          ;
    CaenHVCrateValue<std::string> fIPNetMsk        ;
    CaenHVCrateValue<std::string> fIPGw            ;
    CaenHVCrateValue<std::string> fPWCurrent       ;
    CaenHVCrateValue<uint16_t   > fOutputLevel     ;
    CaenHVCrateValue<std::string> fSymbolicName    ;
    CaenHVCrateValue<uint16_t   > fCmdQueueStatus  ;
    CaenHVCrateValue<std::string> fCPULoad         ;
    CaenHVCrateValue<std::string> fMemoryStatus    ;

    //CaenHVCrateValue<std::string> fResFlag      ;  //not documented
    //CaenHVCrateValue<std::string> fHVFanSpeed   ;  //not documented
    //CaenHVCrateValue<std::string> fPWFanStat    ;  //not documented
    //CaenHVCrateValue<std::string> fPWVoltage    ;  //not documented
    //CaenHVCrateValue<std::string> fDummyReg     ;  //not documented
    //CaenHVCrateValue<std::string> fCMDExecMode  ;  //not documented


  private:
    void GetInfoAllLocal(std::stringstream& ss);

  public:
    void DebugDump(){
      std::stringstream ss;
      ss.str(std::string());ss.clear();ss<<"fSessions       "<<fSessions      .GetVal()<<" @- "<<fSessions      .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fModelName      "<<fModelName     .GetVal()<<" @- "<<fModelName     .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fSwRelease      "<<fSwRelease     .GetVal()<<" @- "<<fSwRelease     .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fGenSignCfg     "<<fGenSignCfg    .GetVal()<<" @- "<<fGenSignCfg    .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fFrontPanIn     "<<fFrontPanIn    .GetVal()<<" @- "<<fFrontPanIn    .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fFrontPanOut    "<<fFrontPanOut   .GetVal()<<" @- "<<fFrontPanOut   .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fResFlagCfg     "<<fResFlagCfg    .GetVal()<<" @- "<<fResFlagCfg    .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fHvPwSM         "<<fHvPwSM        .GetVal()<<" @- "<<fHvPwSM        .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fHVFanStat      "<<fHVFanStat     .GetVal()<<" @- "<<fHVFanStat     .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fClkFreq        "<<fClkFreq       .GetVal()<<" @- "<<fClkFreq       .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fHVClkConf      "<<fHVClkConf     .GetVal()<<" @- "<<fHVClkConf     .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fIPAddr         "<<fIPAddr        .GetVal()<<" @- "<<fIPAddr        .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fIPNetMsk       "<<fIPNetMsk      .GetVal()<<" @- "<<fIPNetMsk      .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fIPGw           "<<fIPGw          .GetVal()<<" @- "<<fIPGw          .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fPWCurrent      "<<fPWCurrent     .GetVal()<<" @- "<<fPWCurrent     .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fOutputLevel    "<<fOutputLevel   .GetVal()<<" @- "<<fOutputLevel   .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fSymbolicName   "<<fSymbolicName  .GetVal()<<" @- "<<fSymbolicName  .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fCmdQueueStatus "<<fCmdQueueStatus.GetVal()<<" @- "<<fCmdQueueStatus.GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fCPULoad        "<<fCPULoad       .GetVal()<<" @- "<<fCPULoad       .GetAge();INFO(ss.str());
      ss.str(std::string());ss.clear();ss<<"fMemoryStatus   "<<fMemoryStatus  .GetVal()<<" @- "<<fMemoryStatus  .GetAge();INFO(ss.str());
    }
};



class DrvCaenSY4527:public VCaenHVMainFrame {
  public:
    DrvCaenSY4527(const std::string& s, VDeviceBase*d):VCaenHVMainFrame(s,d){}
    void AssertMainFrameType(){}
    void GetSysProp_Sessions      ();
    void GetSysProp_ModelName     ();
    void GetSysProp_SwRelease     ();
    void GetSysProp_GenSignCfg    ();
    void GetSysProp_FrontPanIn    ();
    void GetSysProp_FrontPanOut   ();
    void GetSysProp_ResFlagCfg    ();
    void GetSysProp_HvPwSM        ();
    void GetSysProp_HVFanStat     ();
    void GetSysProp_ClkFreq       ();
    void GetSysProp_HVClkConf     ();
    void GetSysProp_IPAddr        ();
    void GetSysProp_IPNetMsk      ();
    void GetSysProp_IPGw          ();
    void GetSysProp_PWCurrent     ();
    void GetSysProp_OutputLevel   ();
    void GetSysProp_SymbolicName  ();
    void GetSysProp_CmdQueueStatus();
    void GetSysProp_CPULoad       ();
    void GetSysProp_MemoryStatus  ();
};

#endif
