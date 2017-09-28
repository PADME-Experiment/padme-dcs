#ifndef  _DCS_kernel_caenhv_CaenSY4527_h_
#define  _DCS_kernel_caenhv_CaenSY4527_h_ 1
#include "CaenSY4527.h"   //in c file

#include<vector>


#include "fwk/fwkException.hh"
class CaenSY4527_except:public fwk::Exception{
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

    //CaenSY4527_except(){fType="CaenSY4527_except";}
    static CaenSY4527_except& CAENWrapperRetStatus(int i,int retstat,const std::string& add=std::string());
    CaenSY4527_except(const std::string&a):fwk::Exception(a){}
    //virtual ~CaenSY4527_except(){}
};
    class CaenSY4527_except::Except_OK                   : public CaenSY4527_except {public: Except_OK                  (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_SYSERR               : public CaenSY4527_except {public: Except_SYSERR              (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_WRITEERR             : public CaenSY4527_except {public: Except_WRITEERR            (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_READERR              : public CaenSY4527_except {public: Except_READERR             (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_TIMEERR              : public CaenSY4527_except {public: Except_TIMEERR             (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_DOWN                 : public CaenSY4527_except {public: Except_DOWN                (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_NOTPRES              : public CaenSY4527_except {public: Except_NOTPRES             (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_SLOTNOTPRES          : public CaenSY4527_except {public: Except_SLOTNOTPRES         (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_NOSERIAL             : public CaenSY4527_except {public: Except_NOSERIAL            (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_MEMORYFAULT          : public CaenSY4527_except {public: Except_MEMORYFAULT         (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_OUTOFRANGE           : public CaenSY4527_except {public: Except_OUTOFRANGE          (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_EXECCOMNOTIMPL       : public CaenSY4527_except {public: Except_EXECCOMNOTIMPL      (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_GETPROPNOTIMPL       : public CaenSY4527_except {public: Except_GETPROPNOTIMPL      (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_SETPROPNOTIMPL       : public CaenSY4527_except {public: Except_SETPROPNOTIMPL      (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_PROPNOTFOUND         : public CaenSY4527_except {public: Except_PROPNOTFOUND        (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_EXECNOTFOUND         : public CaenSY4527_except {public: Except_EXECNOTFOUND        (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_NOTSYSPROP           : public CaenSY4527_except {public: Except_NOTSYSPROP          (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_NOTGETPROP           : public CaenSY4527_except {public: Except_NOTGETPROP          (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_NOTSETPROP           : public CaenSY4527_except {public: Except_NOTSETPROP          (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_NOTEXECOMM           : public CaenSY4527_except {public: Except_NOTEXECOMM          (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_SYSCONFCHANGE        : public CaenSY4527_except {public: Except_SYSCONFCHANGE       (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_PARAMPROPNOTFOUND    : public CaenSY4527_except {public: Except_PARAMPROPNOTFOUND   (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_PARAMNOTFOUND        : public CaenSY4527_except {public: Except_PARAMNOTFOUND       (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_NODATA               : public CaenSY4527_except {public: Except_NODATA              (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_DEVALREADYOPEN       : public CaenSY4527_except {public: Except_DEVALREADYOPEN      (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_TOOMANYDEVICEOPEN    : public CaenSY4527_except {public: Except_TOOMANYDEVICEOPEN   (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_INVALIDPARAMETER     : public CaenSY4527_except {public: Except_INVALIDPARAMETER    (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_FUNCTIONNOTAVAILABLE : public CaenSY4527_except {public: Except_FUNCTIONNOTAVAILABLE(const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_SOCKETERROR          : public CaenSY4527_except {public: Except_SOCKETERROR         (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_COMMUNICATIONERROR   : public CaenSY4527_except {public: Except_COMMUNICATIONERROR  (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_NOTYETIMPLEMENTED    : public CaenSY4527_except {public: Except_NOTYETIMPLEMENTED   (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_CONNECTED            : public CaenSY4527_except {public: Except_CONNECTED           (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_NOTCONNECTED         : public CaenSY4527_except {public: Except_NOTCONNECTED        (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_OS                   : public CaenSY4527_except {public: Except_OS                  (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_LOGINFAILED          : public CaenSY4527_except {public: Except_LOGINFAILED         (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_LOGOUTFAILED         : public CaenSY4527_except {public: Except_LOGOUTFAILED        (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_LINKNOTSUPPORTED     : public CaenSY4527_except {public: Except_LINKNOTSUPPORTED    (const std::string&s):CaenSY4527_except(s){}; };
    class CaenSY4527_except::Except_USERPASSFAILED       : public CaenSY4527_except {public: Except_USERPASSFAILED      (const std::string&s):CaenSY4527_except(s){}; };

class CaenSY4527{
  public:
    CaenSY4527(){
      ComInit();
      GetCrateMap();
      GetExecCommList();
      GetSysPropList();
    }
    ~CaenSY4527(){
      ComDeinit();
    }
  private:
    void ComDeinit();
    void ComInit(
        const std::string&ipaddr="192.168.0.1",
        const std::string&user="admin",
        const std::string&pass="admin");
    void GetCrateMap();
    void GetExecCommList();
    void GetSysPropList();



  private:
    int fCaenCrateHandle;


    private:
    void ConvCharListVector(unsigned short n,const char*
    l,std::vector<std::string>&v);
};


#endif
