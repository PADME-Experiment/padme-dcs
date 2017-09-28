#ifndef  _DCS_kernel_caenhv_CaenSY4527_h_
#define  _DCS_kernel_caenhv_CaenSY4527_h_ 1
#include "CaenSY4527.h"   //in c file


#include "fwk/fwkException.hh"
class CaenSY4527_except:public fwk::Exception{
  public:
    CaenSY4527_except(){fType="CaenSY4527_except";}
    CaenSY4527_except& CommunicationFailure(int i,const std::string& add=std::string());
};



class CaenSY4527{
  public:
    CaenSY4527();
    ~CaenSY4527();
  private:
    void ComDeinit();
    void ComInit(
        const std::string&ipaddr="192.168.0.1",
        const std::string&user="admin",
        const std::string&pass="admin");
    void GetCrateMap();
  private:
    int fCaenCrateHandle;
};


#endif
