#ifndef  _DCS_kernel_drv_DrvCaenHV_h_
#define  _DCS_kernel_drv_DrvCaenHV_h_ 1
#include "DrvCaenHV.h"   //in c file

#include"VDeviceDriver.h"
#include "VCaenHVBoard.h"


#include "fwk/fwkException.h"
#include "fwk/utlMessageBus.h"

#include<vector>
#include<memory>
#include<cstdint>
#include<sstream>
class DrvCaenHV_except:public fwk::Exception{
  public:
    class Except_OK                   ;
    class Except_SYSERR               ;
    class Except_WRITEERR             ;
    class Except_READERR              ;
    class Except_TIMEERR              ;
    class Except_DOWN                 ;
    class Except_NOTPRES              ;
    class Except_SLOTNOTPRES          ;
    class Except_NOSERIAL             ;
    class Except_MEMORYFAULT          ;
    class Except_OUTOFRANGE           ;
    class Except_EXECCOMNOTIMPL       ;
    class Except_GETPROPNOTIMPL       ;
    class Except_SETPROPNOTIMPL       ;
    class Except_PROPNOTFOUND         ;
    class Except_EXECNOTFOUND         ;
    class Except_NOTSYSPROP           ;
    class Except_NOTGETPROP           ;
    class Except_NOTSETPROP           ;
    class Except_NOTEXECOMM           ;
    class Except_SYSCONFCHANGE        ;
    class Except_PARAMPROPNOTFOUND    ;
    class Except_PARAMNOTFOUND        ;
    class Except_NODATA               ;
    class Except_DEVALREADYOPEN       ;
    class Except_TOOMANYDEVICEOPEN    ;
    class Except_INVALIDPARAMETER     ;
    class Except_FUNCTIONNOTAVAILABLE ;
    class Except_SOCKETERROR          ;
    class Except_COMMUNICATIONERROR   ;
    class Except_NOTYETIMPLEMENTED    ;
    class Except_CONNECTED            ;
    class Except_NOTCONNECTED         ;
    class Except_OS                   ;
    class Except_LOGINFAILED          ;
    class Except_LOGOUTFAILED         ;
    class Except_LINKNOTSUPPORTED     ;
    class Except_USERPASSFAILED       ;
  public:

    //DrvCaenHV_except(){fType="DrvCaenHV_except";}
    static DrvCaenHV_except& CAENWrapperRetStatus(int i,int retstat,const std::string& add=std::string());
    DrvCaenHV_except(const std::string&a):fwk::Exception(a){}
    //virtual ~DrvCaenHV_except(){}
};



class DrvCaenHV_except::Except_OK                   : public DrvCaenHV_except {public: Except_OK                  (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_SYSERR               : public DrvCaenHV_except {public: Except_SYSERR              (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_WRITEERR             : public DrvCaenHV_except {public: Except_WRITEERR            (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_READERR              : public DrvCaenHV_except {public: Except_READERR             (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_TIMEERR              : public DrvCaenHV_except {public: Except_TIMEERR             (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_DOWN                 : public DrvCaenHV_except {public: Except_DOWN                (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_NOTPRES              : public DrvCaenHV_except {public: Except_NOTPRES             (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_SLOTNOTPRES          : public DrvCaenHV_except {public: Except_SLOTNOTPRES         (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_NOSERIAL             : public DrvCaenHV_except {public: Except_NOSERIAL            (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_MEMORYFAULT          : public DrvCaenHV_except {public: Except_MEMORYFAULT         (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_OUTOFRANGE           : public DrvCaenHV_except {public: Except_OUTOFRANGE          (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_EXECCOMNOTIMPL       : public DrvCaenHV_except {public: Except_EXECCOMNOTIMPL      (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_GETPROPNOTIMPL       : public DrvCaenHV_except {public: Except_GETPROPNOTIMPL      (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_SETPROPNOTIMPL       : public DrvCaenHV_except {public: Except_SETPROPNOTIMPL      (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_PROPNOTFOUND         : public DrvCaenHV_except {public: Except_PROPNOTFOUND        (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_EXECNOTFOUND         : public DrvCaenHV_except {public: Except_EXECNOTFOUND        (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_NOTSYSPROP           : public DrvCaenHV_except {public: Except_NOTSYSPROP          (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_NOTGETPROP           : public DrvCaenHV_except {public: Except_NOTGETPROP          (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_NOTSETPROP           : public DrvCaenHV_except {public: Except_NOTSETPROP          (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_NOTEXECOMM           : public DrvCaenHV_except {public: Except_NOTEXECOMM          (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_SYSCONFCHANGE        : public DrvCaenHV_except {public: Except_SYSCONFCHANGE       (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_PARAMPROPNOTFOUND    : public DrvCaenHV_except {public: Except_PARAMPROPNOTFOUND   (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_PARAMNOTFOUND        : public DrvCaenHV_except {public: Except_PARAMNOTFOUND       (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_NODATA               : public DrvCaenHV_except {public: Except_NODATA              (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_DEVALREADYOPEN       : public DrvCaenHV_except {public: Except_DEVALREADYOPEN      (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_TOOMANYDEVICEOPEN    : public DrvCaenHV_except {public: Except_TOOMANYDEVICEOPEN   (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_INVALIDPARAMETER     : public DrvCaenHV_except {public: Except_INVALIDPARAMETER    (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_FUNCTIONNOTAVAILABLE : public DrvCaenHV_except {public: Except_FUNCTIONNOTAVAILABLE(const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_SOCKETERROR          : public DrvCaenHV_except {public: Except_SOCKETERROR         (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_COMMUNICATIONERROR   : public DrvCaenHV_except {public: Except_COMMUNICATIONERROR  (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_NOTYETIMPLEMENTED    : public DrvCaenHV_except {public: Except_NOTYETIMPLEMENTED   (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_CONNECTED            : public DrvCaenHV_except {public: Except_CONNECTED           (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_NOTCONNECTED         : public DrvCaenHV_except {public: Except_NOTCONNECTED        (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_OS                   : public DrvCaenHV_except {public: Except_OS                  (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_LOGINFAILED          : public DrvCaenHV_except {public: Except_LOGINFAILED         (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_LOGOUTFAILED         : public DrvCaenHV_except {public: Except_LOGOUTFAILED        (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_LINKNOTSUPPORTED     : public DrvCaenHV_except {public: Except_LINKNOTSUPPORTED    (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };
class DrvCaenHV_except::Except_USERPASSFAILED       : public DrvCaenHV_except {public: Except_USERPASSFAILED      (const std::string&s):DrvCaenHV_except(s){ fwk::Exception::SetType(*this); }; };









class DrvCaenHV:public VDeviceDriver{
  public:
    void Finalize(){Deinitialize();JoinThread();}
    //DrvCaenHV(){INFO("DEBUG");}
    DrvCaenHV(const std::string&lab,VDeviceBase*parp)
    :VDeviceDriver(lab,parp)
  {
    INFO("pars");
  }
    ~DrvCaenHV(){
      //ComDeinit();
      INFO("");
    }
    ///Opens a Caen comm and passes the handle to subdevices
    void SetParams(std::set<std::string>);
    void OnStart() {/* TODO opens handle and call all daughter AssertInits*/}
    void OnCycle() {std::this_thread::sleep_for(std::chrono::seconds(3));DebugUpdate();
      VDeviceDriver::ElemIter devit;
      devit=static_cast<VDeviceDriver::ElemIter>(nullptr);
      while(GetNext(devit)){devit->second->DebugUpdate();}
    }
    void OnStop()  {}
    //void ConnectToDevice() {fCaenCrateHandle=ComInit  ();}
    //void DisconnectDevice(){ComDeinit();}
    void DebugUpdate(){
      INFO("");
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
      //DebugDump();
    }


  public:
    void GetCrateMap();
    void GetExecCommList();
    void GetSysPropList();
    void SetIPAddress(const std::string&s){fIPAddress=s;}
    void SetUsername (const std::string&s){fUsername =s;}
    void SetPassword (const std::string&s){fPassword =s;};
    void AssertInit();
    void Deinitialize();
    int  GetCaenCrateHandle(){return fCaenCrateHandle;}





  private:
    void ComDeinit(int);
    int  ComInit();

  private:
    int fCaenCrateHandle; ///< This handle is to be used only for reading. All Setters shoul open new one!!!
    std::string fIPAddress;
    std::string fUsername;
    std::string fPassword;



  private:
    void ConvCharListVector(unsigned short n,const char*
        l,std::vector<std::string>&v);


  public:
    void GetSysProp(const std::string&cmd, void* res);
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




  private: // values
    CaenHVValue<std::string> fSessions        ;
    CaenHVValue<std::string> fModelName       ;
    CaenHVValue<std::string> fSwRelease       ;
    CaenHVValue<uint16_t   > fGenSignCfg      ;
    CaenHVValue<uint16_t   > fFrontPanIn      ;
    CaenHVValue<uint16_t   > fFrontPanOut     ;
    CaenHVValue<uint16_t   > fResFlagCfg      ;
    CaenHVValue<std::string> fHvPwSM          ;
    CaenHVValue<std::string> fHVFanStat       ;
    CaenHVValue<uint16_t   > fClkFreq         ;
    CaenHVValue<std::string> fHVClkConf       ;
    CaenHVValue<std::string> fIPAddr          ;
    CaenHVValue<std::string> fIPNetMsk        ;
    CaenHVValue<std::string> fIPGw            ;
    CaenHVValue<std::string> fPWCurrent       ;
    CaenHVValue<uint16_t   > fOutputLevel     ;
    CaenHVValue<std::string> fSymbolicName    ;
    CaenHVValue<uint16_t   > fCmdQueueStatus  ;
    CaenHVValue<std::string> fCPULoad         ;
    CaenHVValue<std::string> fMemoryStatus    ;

    //CaenHVValue<std::string> fResFlag      ;  //not documented
    //CaenHVValue<std::string> fHVFanSpeed   ;  //not documented
    //CaenHVValue<std::string> fPWFanStat    ;  //not documented
    //CaenHVValue<std::string> fPWVoltage    ;  //not documented
    //CaenHVValue<std::string> fDummyReg     ;  //not documented
    //CaenHVValue<std::string> fCMDExecMode  ;  //not documented


  public: // DEBUG
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


#endif
