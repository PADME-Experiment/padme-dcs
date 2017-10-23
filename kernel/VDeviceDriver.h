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
    VDeviceBase(const std::string& lab,VDeviceBase* par):fParent(par){
      fLabel=(HasParent()?GetParent()->GetName()+"/"+lab:lab);}
    virtual ~VDeviceBase(){INFO(fLabel);}
  public:
    typedef struct {
      std::string cmd;
      unsigned int interval;
    } update_par_t;
  protected:
    void AssertInitAllOwned(){INFO(fLabel);for(auto it=fDevs. begin();it!=fDevs. end();++it){it->second.get()->AssertInit();}}
  public:
    virtual void AssertInit(){AssertInitAllOwned();}
    void Finalize  (){for(auto it=fDevs.rbegin();it!=fDevs.rend();++it){it->second.get()->Finalize  ();}}
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
    void SetParams(std::set<std::string>);
    /// This function should be called from AssertInit
    void SetUpdate(const std::string&what,unsigned int interval);
    bool HasParent()const{return (fParent!=nullptr);}
    ///Updates all parameters of the current device and all
    ///sub devices
    void UpdateAll();
  protected:
    ///covers only "*" case but anything can be implemented
    virtual void SetLocalUpdate(const std::string&what,unsigned int interval);
    virtual void SetLocalParams(std::set<std::string>)=0;
    virtual void UpdateAllLocal(const std::string&str)=0;
    std::string fLabel; ///< full path PADME/xxx/yyy/zzz
    std::map<std::string,std::shared_ptr<VDeviceBase>> fDevs;
    VDeviceBase* fParent;
  public:
    //virtual void DebugUpdate(){UpdateAllParameters();}  //TODO tezi da se mahnat
    virtual void DebugDump(){}

  private:
    std::multimap<time_t,update_par_t>fScheduledUpdates;
};




#include<ctime>

/* Any primary device. Those wich will be part of the main
 * layout and which will maintain connection with physical
 * devices
 */
class VDeviceDriver:public VDeviceBase, public VDaemonSingleThread{
  public:
    VDeviceDriver(const std::string& lab,VDeviceBase* par):VDeviceBase(lab,par){}
    virtual ~VDeviceDriver(){}

    const std::string& GetName()const{return VDeviceBase::GetName();}

    ///Connect to the device and keep the connection
    virtual void ConnectToDevice(){} //TODO should be pure maybe
    ///Disconnect from the device
    virtual void DisconnectDevice(){} //TODO should be pure maybe

    //virtual void AssertInit()=0;
    //virtual void Deinitialize(){}
    //void AddUpdateToTmpList(const std::string&what,unsigned int interval){
    //  fUpdateListTemp.insert(std::multimap<std::string,unsigned int>::value_type(what,interval));
    //}
    ///This is to be called from AsserInit
    //void ProcessUpdateListTemp(){
    //  for(auto it=fUpdateListTemp.begin();it!=fUpdateListTemp.end();++it){
    //    this->VDeviceBase::SetUpdate(it->first,it->second);
    //  }
    //  fUpdateListTemp.clear();
    //}

    //std::multimap<std::string,unsigned int>fUpdateListTemp;
};


#endif
