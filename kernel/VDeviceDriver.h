#ifndef  _DCS_kernel_VDeviceDriver_h_
#define  _DCS_kernel_VDeviceDriver_h_ 1
#include "kernel/VDeviceDriver.h"   //in c file
#include "kernel/VDaemon.h"
#include "fwk/fwkException.h"
#include "fwk/utlMessageBus.h"
#include<string>
#include<memory>
#include<map>
#include<set>
#include<sstream>


class VDeviceDriver{
  public:
    typedef std::map<std::string,std::shared_ptr<VDeviceDriver>>::iterator ElemIter;
    VDeviceDriver(const std::string& lab,std::shared_ptr<VDeviceDriver> par):fLabel(lab),fParent(par){}
    virtual ~VDeviceDriver(){}
    std::shared_ptr<VDeviceDriver> AddDevice(const std::string& lab, std::shared_ptr<VDeviceDriver>ptr);
    std::shared_ptr<VDeviceDriver>Get(const std::string& str){return fAllDevs.at(str);} //TODO try throw proper exception
    std::shared_ptr<VDeviceDriver>GetParent(){if(fParent.use_count()==0)throw FIXME_EXCEPTION("Parent doesnt exist ");else return fParent;}
    const std::string& GetName()const{return fLabel;}
    virtual void DebugUpdate(){}
    virtual void DebugDump(){}
    ///Connect to the device and keep the connection
    virtual void ConnectToDevice(){} //TODO should be pure maybe
    ///Disconnect from the device
    virtual void DisconnectDevice(){} //TODO should be pure maybe
    bool HasParent()const{return (fParent.use_count()>0);}
    ///Parses commands in the strings and sets parameters.
    ///The default is to send the strings to sub-devices.
    virtual void SetParams(std::set<std::string>);

    /**
     * Cycle through all devices.
     * \returns false when there are no more devices.
     */
    bool GetNext(ElemIter& it /**<[inout]*/);
    virtual void AssertInit(){}
    virtual void Deinitialize(){}
  protected:
    std::string fLabel;
    std::map<std::string,std::shared_ptr<VDeviceDriver>> fAllDevs;
    std::shared_ptr<VDeviceDriver> fParent;
};


#endif
