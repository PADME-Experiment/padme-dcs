#ifndef  _DCS_kernel_DeviceManager_h_
#define  _DCS_kernel_DeviceManager_h_ 1
#include "kernel/DeviceManager.h"   //in c file
#include "VDeviceDriver.h"
#include "VDaemon.h"

#include<string>
#include<map>
#include<memory>

class DeviceManager:public VDeviceBase{
  public:
    void AssertInit();
    void Daemonize();
    void Finalize();
  public:
    static DeviceManager& GetInstance();
    void Configure(const std::string& cfg);

  private:
std::shared_ptr<VDaemonBase> AddDaemon(const std::string& lab, std::shared_ptr<VDaemonBase>ptr);
    std::map<std::string,std::shared_ptr<VDaemonBase>> fDems;
    DeviceManager():VDeviceBase("PADME",nullptr){TrapKillSignals();}
    ~DeviceManager(){SUCCESS("");}

  public:
    void MainLoop();
  private:
    void TrapKillSignals();
    static void Sigint(int i);
    static bool fsPrepareForQuit;
};


#endif
