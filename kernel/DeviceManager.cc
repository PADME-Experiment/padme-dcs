#include "kernel/DeviceManager.h"   //in c file
#include "yaml-cpp/yaml.h"
#include "fwk/utlMessageBus.h"
#include "DrvCaenHV.h"
#include "DrvCaenA7030.h"
#include<memory>
#include<fstream>

  DeviceManager&
DeviceManager::GetInstance()
{
  static DeviceManager a;
  return a;
}

  void
DeviceManager::ProcessConfig(const std::string& cfg)
{
  std::ifstream yamlconfigf(cfg);
  YAML::Node config = YAML::Load(yamlconfigf);
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
      //caen->ComInit();
    }else if(drvtype=="NYAKOJ DRUG DETEKTOR"){
    }
  }


  for(int nod_i=0;nod_i<config.size();++nod_i){
    if(config[nod_i]["ParentLabel"].as<std::string>().size()==0)
      continue;
    const std::string& drvtype=config[nod_i]["DriverType" ].as<std::string>();
    const std::string& devlble=config[nod_i]["Label"      ].as<std::string>();
    const std::string& parlble=config[nod_i]["ParentLabel"].as<std::string>();
    if(drvtype=="CAEN_A7030"){
      auto board=std::dynamic_pointer_cast<DrvCaenA7030>(
          AddDevice(devlble,std::make_shared<DrvCaenA7030>(devlble,Get(parlble)))
          );
      board->GetParentInfo();
      board->SetNumChannels ( config[nod_i]["Args"]["NChannels"  ].as<unsigned int>());
      board->SetSlot        ( config[nod_i]["Args"]["Slot"       ].as<unsigned int>());
    }else if(drvtype=="NYAKOJ DRUG DETEKTOR"){
    }
  }
  VDeviceDriver::ElemIter devit=static_cast<VDeviceDriver::ElemIter>(nullptr);
  while(GetNext(devit)){devit->second->DebugInfo();}



}

