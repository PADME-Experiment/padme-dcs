extern "C"{
#include"V8100.h"
}
#include<iostream>
#include <unistd.h>


int main(int argc, char *argv[]){
  if(argc!=2){std::cerr<< "synopsis: "<<argv[0]<<"  <IP>"<<std::endl;return 1;}
  char* ip=argv[1];
  V8100_data handler;
  CMD_ERROR_CODE err;
  V8100_open_eth(&handler,ip);

  UINT8 ui8;
  UINT32 ui32;
  const int length=100;
  char chararr[length];
  float f;
  bool ret_bool;

  V8100_set_on(&handler,&err);
  V8100_close(&handler);
  return 0;
}
