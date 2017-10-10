#include"kernel/DeviceManager.h"   //in c file
#include"DrvCaenHV.h"
#include"DrvCaenA7030.h"
#include"fwk/utlMessageBus.h"
#include<yaml-cpp/yaml.h>
#include<memory>
#include<csignal>



class HVDumper: public VDaemonSingleThread{
// FIXME this is to be removed
// FIXME EXAMPLE
  void OnStart() {}
  void OnCycle() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    DeviceManager::GetInstance().Get("CAENHV1")->DebugDump();
    DeviceManager::GetInstance().Get("CAENHV1")->Get("CAENHV1.board1")->DebugDump();
  }
  void OnStop(){}
};





  DeviceManager&
DeviceManager::GetInstance()
{
  static DeviceManager a;
  return a;
}


  void
DeviceManager::ProcessConfig(const std::string& cfg)
{
  TrapKillSignals();

  YAML::Node config = YAML::LoadFile(cfg);
  for(int nod_i=0;nod_i<config.size();++nod_i){
    if(config[nod_i]["ParentLabel"].as<std::string>()!="PADME")
      continue; // non global device
    const std::string& drvtype=config[nod_i]["DriverType"].as<std::string>();
    const std::string& devlble=config[nod_i]["Label"     ].as<std::string>();
    if(drvtype=="CAEN_SY4527"){
      auto caen=std::dynamic_pointer_cast<DrvCaenHV>(
          AddDevice(devlble,std::make_shared<DrvCaenHV>(devlble,nullptr))
          );
      caen->SetIPAddress( config[nod_i]["Args"]["IPAddr"].as<std::string>());
      caen->SetUsername ( config[nod_i]["Args"]["User"  ].as<std::string>());
      caen->SetPassword ( config[nod_i]["Args"]["Pass"  ].as<std::string>());
    }else if(drvtype=="NYAKOJ DRUG DETEKTOR"){
    }
  }
  for(int nod_i=0;nod_i<config.size();++nod_i){
    if(config[nod_i]["ParentLabel"].as<std::string>().size()==0)
      continue;
    const std::string& drvtype=config[nod_i]["DriverType" ].as<std::string>();
    const std::string& devlble=config[nod_i]["Label"      ].as<std::string>();
    const std::string& parlble=config[nod_i]["ParentLabel"].as<std::string>();
    if(drvtype=="CAEN_A7030N"){
      auto board=std::dynamic_pointer_cast<DrvCaenA7030N>(
          Get(parlble)->AddDevice(devlble,std::make_shared<DrvCaenA7030N>(devlble,Get(parlble)))
          );
      board->GetParentInfo();
      board->SetNumChannels ( config[nod_i]["Args"]["NChannels"  ].as<unsigned int>());
      board->SetSlot        ( config[nod_i]["Args"]["Slot"       ].as<unsigned int>());
      board->AssertInit();
    }else if(drvtype=="NYAKOJ DRUG DETEKTOR"){
    }
  }

  VDeviceDriver::ElemIter devit;
  devit=static_cast<VDeviceDriver::ElemIter>(nullptr);
  //while(GetNext(devit)){devit->second->AssertInit();}

  HVDumper hvdumper;
  ServiceTCPConfigure confTCP(33455);

  confTCP.Daemonize();
  MainLoop();


  std::dynamic_pointer_cast<VDaemonSingleThread>(Get("CAENHV1"))->Daemonize();

  hvdumper.Daemonize();



  INFO("will join caenhv");
  std::dynamic_pointer_cast<VDaemonSingleThread>(DeviceManager::GetInstance().Get("CAENHV1"))->JoinThread();
  SUCCESS("caenhv joined");
  INFO("will join hvdumper");
  hvdumper.JoinThread();
  SUCCESS("hvdumper joined");

  devit=static_cast<VDeviceDriver::ElemIter>(nullptr);
  while(GetNext(devit)){devit->second->Deinitialize();}


}

static bool gPrepareForQuit=false;

  static void
Sigint(int i)
{
  INFO("CTRL-C Received");
  gPrepareForQuit=true;
}

  void
DeviceManager::MainLoop()
{
  int i=0;
  while(!gPrepareForQuit){
    if((++i%10)==0)INFO("ALLIVE!");
    std::this_thread::sleep_for( std::chrono::milliseconds(200));
  }
}

  void
DeviceManager::TrapKillSignals()
{
  signal(SIGINT , Sigint);
}
