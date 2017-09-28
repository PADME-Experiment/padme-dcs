#include "caenhv/CaenSY4527.h"
#include<iostream>
int main(){

try{
  CaenSY4527 a;
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
