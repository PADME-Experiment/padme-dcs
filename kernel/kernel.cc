#include "caenhv/CaenSY4527.h"
#include<iostream>
int main(){

try{
  CaenSY4527 a;
}
catch(const std::exception& e){
  std::cerr<<e.what()<<std::endl;
}
  return 0;
}
