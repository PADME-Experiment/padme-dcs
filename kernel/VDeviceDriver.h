#ifndef  _DCS_kernel_VDeviceDriver_h_
#define  _DCS_kernel_VDeviceDriver_h_ 1
#include "VDeviceDriver.h"   //in c file
#include "VDaemon.h"
#include "fwk/fwkException.h"
#include "fwk/utlMessageBus.h"
#include<string>
#include<memory>
#include<map>
#include<sstream>


class VDeviceDriver{
  public:
  typedef std::map<std::string,std::shared_ptr<VDeviceDriver>>::iterator ElemIter;
    VDeviceDriver(const std::string& lab,std::shared_ptr<VDeviceDriver> par):fLabel(lab),fParent(par){}
    virtual ~VDeviceDriver(){}
    std::shared_ptr<VDeviceDriver> AddDevice(const std::string& lab, std::shared_ptr<VDeviceDriver>ptr);

    std::shared_ptr<VDeviceDriver>Get(const std::string& str){return fAllDevs.at(str);}
    std::shared_ptr<VDeviceDriver>GetParent(){if(fParent.use_count()==0)throw FIXME_EXCEPTION("Parent doesnt exist ");else return fParent;}
    const std::string& GetName()const{return fLabel;}
    virtual void DebugInfo(){}

    bool GetNext(ElemIter& it);
    void AssertInit();
  protected:
    std::string fLabel;
    std::map<std::string,std::shared_ptr<VDeviceDriver>> fAllDevs;
    std::shared_ptr<VDeviceDriver> fParent;
};

class VDeviceDriverDaemonizable:public VDeviceDriver,public VDaemonSingleThread{
  public:
    VDeviceDriverDaemonizable(
        const std::string& lab,
        std::shared_ptr<VDeviceDriver> par):
      VDeviceDriver(lab,par){}
};



#endif
