#include "CaenSY4527.h"   //in c file
#include <caenlib/CAENHVWrapper.h>

  CaenSY4527_except&
CaenSY4527_except::CommunicationFailure(int i)
{
  fWhat="File '"+std::to_string(i)+"' cannot be created.";
  return *this;
}

CaenSY4527::CaenSY4527(){
  ComInit();




}

CaenSY4527::~CaenSY4527(){
}



  void
CaenSY4527::ComInit(
    const std::string&ipaddr,
    const std::string&user,
    const std::string&pass)
{

  CAENHVRESULT ret;
  CAENHV_SYSTEM_TYPE_t sys_type = (CAENHV_SYSTEM_TYPE_t) SY4527; // 0: SY1527, 2: SY4527
  int link_type = LINKTYPE_TCPIP;
  ret = CAENHV_InitSystem(sys_type, link_type, (void*)ipaddr.c_str(), "admin", "admin", &fCaenCrateHandle);
  if(ret != CAENHV_OK){
    throw  CaenSY4527_except().CommunicationFailure(4);
  }
  //fprintf(stderr,"ERROR!!! ===> CAENHV_InitSystem: %s (num. %d)\n\n", CAENHV_GetError(handle), ret);
}

















