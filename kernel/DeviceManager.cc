#include "kernel/DeviceManager.h"   //in c file
#include "yaml-cpp/yaml.h"
#include "fwk/utlMessageBus.h"
#include "DrvCaenHV.h"
#include<memory>

  DeviceManager&
DeviceManager::GetInstance()
{
  static DeviceManager a;
  return a;
}

  void
DeviceManager::ProcessConfig(const std::string& cfg)
{
  YAML::Node config = YAML::LoadFile(cfg);
  for(int nod_i=0;nod_i<config.size();++nod_i){
    if(config[nod_i]["ParentLabel"].as<std::string>().size()!=0)
      continue; // non global device
    const std::string& drvtype=config[nod_i]["DriverType"].as<std::string>();
    const std::string& devlble=config[nod_i]["Label"     ].as<std::string>();
    if(drvtype=="CAEN_SY4527"){
      AddDevice(devlble,std::make_shared<DrvCaenHV>(devlble,nullptr));
      //DrvCaenHV& caen=dynamic_cast<DrvCaenHV&>(Get(devlble));
      //caen.ComInit(
      //    config[nod_i]["Args"]["IPAddr"].as<std::string>(),
      //    config[nod_i]["Args"]["User"  ].as<std::string>(),
      //    config[nod_i]["Args"]["Pass"  ].as<std::string>());
    }else if(drvtype=="NYAKOJ DRUG DETEKTOR"){
    }
  }


//  for(int nod_i=0;nod_i<config.size();++nod_i){
//    if(config[nod_i]["ParentLabel"].as<std::string>().size()==0)
//      continue;
//    const std::string& drvtype=config[nod_i]["DriverType" ].as<std::string>();
//    const std::string& devlble=config[nod_i]["Label"      ].as<std::string>();
//    const std::string& parlble=config[nod_i]["ParentLabel"].as<std::string>();
//    if(drvtype=="CAEN_A7030"){
//      fAllDevs[devlble]=std::make_unique<DrvCaenHV>(devlble);
//      DrvCaenHV& caen=dynamic_cast<DrvCaenHV&>(*fAllDevs.at(devlble));
//      caen.ComInit(
//          config[nod_i]["Args"]["IPAddr"].as<std::string>(),
//          config[nod_i]["Args"]["User"  ].as<std::string>(),
//          config[nod_i]["Args"]["Pass"  ].as<std::string>());
//    }else if(drvtype=="NYAKOJ DRUG DETEKTOR"){
//    }
//  }



}

