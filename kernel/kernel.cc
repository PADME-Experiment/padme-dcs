#include "drv/DrvCaenHV.h"
#include<iostream>
int main(){

try{
  DrvCaenHV a;
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
