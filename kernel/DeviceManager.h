#ifndef  _DCS_kernel_DeviceManager_h_
#define  _DCS_kernel_DeviceManager_h_ 1
#include "kernel/DeviceManager.h"   //in c file
#include "VDeviceDriver.h"

#include<string>
#include<map>
#include<memory>

class DeviceManager:public VDeviceDriver{
  public:
    static DeviceManager& GetInstance();
    void ProcessConfig(const std::string& cfg);
    void AssertInit(){}
    void Daemonize(){}
    void MainLoop();
    void TrapKillSignals();
  private:
  //std::list<VServices>
    DeviceManager():VDeviceDriver("padme",std::shared_ptr<VDeviceDriver>(nullptr)){}
    ~DeviceManager(){}
};


#endif
