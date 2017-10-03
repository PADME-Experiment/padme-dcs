#ifndef  _DCS_kernel_DrvCaenA7030_h_
#define  _DCS_kernel_DrvCaenA7030_h_ 1
#include "DrvCaenA7030.h"   //in c file
#include "fwk/utlMessageBus.h"
#include "VCaenHVBoard.h"

#include <string>

class DrvCaenA7030:public VCaenHVBoard{
  public:
    DrvCaenA7030(const std::string& s, std::shared_ptr<VDeviceDriver>d):VCaenHVBoard(s,d){INFO("");}
    ~DrvCaenA7030(){INFO("");}
    void GetParentInfo(){INFO(GetParent()->GetName());}
};

#endif
