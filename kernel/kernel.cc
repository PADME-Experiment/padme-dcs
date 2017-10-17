#include "kernel.h"   //in c file

#include "DrvCaenHV.h"
#include<iostream>
#include"fwk/utlMessageBus.h"




int main(){


  DeviceManager& devmngr=DeviceManager::GetInstance();
  INFO("Configure"   );devmngr.Configure("glob.yaml");SUCCESS("Configure"   );
  INFO("AssertInit()");devmngr.AssertInit();          SUCCESS("AssertInit()");
  INFO("Daemonize();");devmngr.Daemonize();           SUCCESS("Daemonize();");
  INFO("MainLoop(); ");devmngr.MainLoop();            SUCCESS("MainLoop(); ");
  INFO("Finalize(); ");devmngr.Finalize();            SUCCESS("Finalize(); ");

  try{
  }
  catch(const fwk::Exception& e){
    std::cerr<<e.what()<<std::endl;
    std::cerr<<e.GetType()<<std::endl;
  }
  catch(const std::exception& e){
    std::cerr<<e.what()<<std::endl;
  }
  return 0;
}
