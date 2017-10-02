#ifndef  _DCS_kernel_DrvCaenA7030_h_
#define  _DCS_kernel_DrvCaenA7030_h_ 1
#include "DrvCaenA7030.h"   //in c file
#include "VDeviceDriver.h"

#include <string>

class DrvCaenA7030:public VDeviceDriver{
  public:
    DrvCaenA7030(const std::string& s, std::shared_ptr<VDeviceDriver>d):VDeviceDriver(s,d){}
    ~DrvCaenA7030(){}
};

#endif
