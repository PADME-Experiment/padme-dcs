#include"kernel/DeviceManager.h"   //in c file
#include"DrvCaenHV.h"
#include"DrvCaenA7030.h"
#include"fwk/utlMessageBus.h"
#include<yaml-cpp/yaml.h>
#include<memory>
#include<csignal>



class HVDumper: public VDeviceDriver{
  // FIXME this is to be removed
  // FIXME EXAMPLE
  public:
    //void Daemonize(){VDaemonSingleThread::Daemonize();}
    void Service(){}
    HVDumper():VDeviceDriver("HVDumper",nullptr){}
    void OnStart() {}
    void OnCycle() {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      DeviceManager::GetInstance().Get("CAENHV1")->DebugDump();
      DeviceManager::GetInstance().Get("CAENHV1")->Get("board1")->DebugDump();
    }
    void OnStop(){}
    void Finalize(){JoinThread();}
    void AssertInit(){}
};





  DeviceManager&
DeviceManager::GetInstance()
{
  static DeviceManager a;
  return a;
}

  std::shared_ptr<VDaemonBase>
DeviceManager::AddDaemon(const std::string& lab, std::shared_ptr<VDaemonBase>ptr)
{
  // TODO: should also set the global name of the device PADME/xxx/yyy/zzz
  // TODO: should check if the device existed before

  fDems[lab]=ptr;
  return ptr;
}

  void
DeviceManager::AssertInit()
{
  // note that DEVICES are FIRST
  this->VDeviceBase::AssertInit();
  for(auto it=fDems. begin();it!=fDems. end();++it){
    INFO(it->second.get()->GetName());
    it->second.get()->AssertInit();
  }
}
  void
DeviceManager::Daemonize ()
{
  // note that DEVICES are FIRST
  for(auto it=fDevs. begin();it!=fDevs. end();++it){
    INFO(it->second.get()->GetName());
    auto dev=std::dynamic_pointer_cast<VDeviceDriver>(it->second);
    if(dev==nullptr)
      ERROR("throw");
    //WARNING("Devices are not daemonized");
    dev->Daemonize ();
  }
  for(auto it=fDems. begin();it!=fDems. end();++it){
    INFO(it->second.get()->GetName());
    it->second.get()->Daemonize ();
  }
}
  void
DeviceManager::Finalize  ()
{
  // note order is reverced
  // reverce iterators are used
  // and DEVICES are LAST
  for(auto it=fDems.rbegin();it!=fDems.rend();++it){
    INFO(it->second.get()->GetName());
    it->second.get()->Finalize  ();
  }
  this->VDeviceBase::Finalize();
  fDems.clear();
  fDevs.clear();
}



  void
DeviceManager::Configure(const std::string& cfg)
{
  YAML::Node config = YAML::LoadFile(cfg);
  for(int nod_i=0;nod_i<config.size();++nod_i){
    const std::string& drvtype=config[nod_i]["DriverType"].as<std::string>();
    const std::string& devlble=config[nod_i]["Label"     ].as<std::string>();
    const std::string& parlble=config[nod_i]["ParentLabel"].as<std::string>();
    if(drvtype=="CAEN_SY4527"){
      auto caen=std::make_shared<DrvCaenHV>(devlble,this); //potential problem
      AddDevice(devlble,caen);
      caen->SetIPAddress( config[nod_i]["Args"]["IPAddr"].as<std::string>());
      caen->SetUsername ( config[nod_i]["Args"]["User"  ].as<std::string>());
      caen->SetPassword ( config[nod_i]["Args"]["Pass"  ].as<std::string>());
    }else if(drvtype=="CAEN_A7030N"){
      auto board=std::make_shared<DrvCaenA7030N>(devlble,Get(parlble).get());
      Get(parlble)->AddDevice(devlble,board);
      board->GetParentInfo();
      board->SetNumChannels ( config[nod_i]["Args"]["NChannels"  ].as<unsigned int>());
      board->SetSlot        ( config[nod_i]["Args"]["Slot"       ].as<unsigned int>());
      //board->AssertInit();
    }else if(drvtype=="ServiceTCPConfigure"){
      unsigned int portn=config[nod_i]["Args"]["TCPPortNumber"  ].as<unsigned int>();
      auto service=std::make_shared<ServiceTCPConfigure>(devlble,portn);
      AddDaemon(devlble,service);
    }
  }




  auto hvdumper=std::make_shared<HVDumper>();
  AddDaemon("hvdumper",hvdumper);


}




bool DeviceManager::fsPrepareForQuit=false;

  void
DeviceManager::Sigint(int i)
{
  INFO("CTRL-C Trapped");
  fsPrepareForQuit=true;
}

  void
DeviceManager::MainLoop()
{
  int i=0;
  while(!fsPrepareForQuit){
    if((++i%10)==0)INFO("ALLIVE!");
    std::this_thread::sleep_for( std::chrono::milliseconds(200));
  }
}

  void
DeviceManager::TrapKillSignals()
{
  signal(SIGINT , Sigint);
}
