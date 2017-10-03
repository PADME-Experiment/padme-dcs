#include "kernel.h"   //in c file

#include "DrvCaenHV.h"
#include<iostream>
#include"fwk/utlMessageBus.h"

int main(){



    DeviceManager::GetInstance().ProcessConfig("glob.yaml");
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
