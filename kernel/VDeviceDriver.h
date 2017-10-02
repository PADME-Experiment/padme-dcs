#ifndef  _DCS_kernel_VDeviceDriver_h_
#define  _DCS_kernel_VDeviceDriver_h_ 1
#include "VDeviceDriver.h"   //in c file
#include "fwk/fwkException.h"
#include<string>
#include<memory>
#include<map>


class VDeviceDriver{
  public:
    VDeviceDriver(const std::string& lab,std::weak_ptr<VDeviceDriver> par):fLabel(lab),fParent(par){}
    virtual ~VDeviceDriver(){}
    void AddDevice(const std::string& lab, std::shared_ptr<VDeviceDriver>ptr);

    std::weak_ptr<VDeviceDriver>Get(const std::string& str){return fAllDevs.at(str);}
    std::weak_ptr<VDeviceDriver>GetParent(){if(fParent.use_count()==0)throw fwk::Exception_tobefixed(std::string(__FILE__)+ "Parent doesnt exist ");else return fParent;}
  protected:
    std::string fLabel;
    std::map<std::string,std::shared_ptr<VDeviceDriver>> fAllDevs;
    std::weak_ptr<VDeviceDriver> fParent;
};

#endif
