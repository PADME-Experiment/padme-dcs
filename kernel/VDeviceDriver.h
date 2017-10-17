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

/// Any hardware piece. Crate or board
class VDeviceBase{
  public:
    VDeviceBase(const std::string& lab,VDeviceBase* par):fLabel(lab),fParent(par){}
    virtual ~VDeviceBase(){}
  public:
    virtual void AssertInit()=0;
    virtual void Finalize  ()=0;
    const std::string& GetName()const{return fLabel;}

    typedef std::map<std::string,std::shared_ptr<VDeviceBase>>::iterator ElemIter;
    /**
     * Cycle through all devices.
     * \returns false when there are no more devices.
     * If called with argument =nullptr cycle starts from
     * the first element. Otherwise, it gives the next one.
     * When last element is reached the pointer is =nullptr.
     */
    bool GetNext(ElemIter& it /**<[inout]*/);
    VDeviceBase*GetParent(){if(fParent==nullptr)throw FIXME_EXCEPTION("Parent doesnt exist ");else return fParent;}
    std::shared_ptr<VDeviceBase>AddDevice(const std::string& lab, std::shared_ptr<VDeviceBase>ptr);
    std::shared_ptr<VDeviceBase>Get(const std::string& str){return fDevs.at(str);} //TODO try throw proper exception
    /*
     * Parses commands in the strings and sets parameters.
     * The default is to send the strings to sub-devices.
     */
    virtual void SetParams(std::set<std::string>);
    bool HasParent()const{return (fParent!=nullptr);}
  protected:
    std::string fLabel; ///< full path PADME/xxx/yyy/zzz
    std::map<std::string,std::shared_ptr<VDeviceBase>> fDevs;
    VDeviceBase* fParent;
  public:
  virtual void DebugUpdate(){}
  virtual void DebugDump(){}
};



/// Any primary device. Those wich will be part of the main
/// layout
class VDeviceDriver:public VDeviceBase, public VDaemonSingleThread{
  public:
    VDeviceDriver(const std::string& lab,VDeviceBase* par):VDeviceBase(lab,par){}
    virtual ~VDeviceDriver(){}

    const std::string& GetName()const{return VDeviceBase::GetName();}


    virtual void DebugUpdate(){}
    virtual void DebugDump(){}
    ///Connect to the device and keep the connection
    virtual void ConnectToDevice(){} //TODO should be pure maybe
    ///Disconnect from the device
    virtual void DisconnectDevice(){} //TODO should be pure maybe

    //virtual void AssertInit()=0;
    //virtual void Deinitialize(){}
};


#endif
