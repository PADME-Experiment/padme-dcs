#include "CaenSY4527.h"   //in c file
#include <caenlib/CAENHVWrapper.h>
#include<iostream>

  CaenSY4527_except&
CaenSY4527_except::CommunicationFailure(int caenhandler,const std::string& add)
{ std::string a(CAENHV_GetError(caenhandler));
  fWhat+="CAENHVWrapper returned error : '" + a + "'";
  if(add.size()>0)fWhat+="\n"+add;
  return *this;
}

CaenSY4527::CaenSY4527(){
  GetCrateMap();
  ComInit();
}


CaenSY4527::~CaenSY4527(){
  ComDeinit();
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
  ret = CAENHV_InitSystem(sys_type, link_type, (void*)ipaddr.c_str(), user.c_str(), pass.c_str(), &fCaenCrateHandle);
  if(ret != CAENHV_OK){
    throw  CaenSY4527_except().CommunicationFailure(fCaenCrateHandle,
    "IP = "+ipaddr+"\nuser = "+user+"\npass = "+pass+"\nreturn value "+std::to_string(ret));
  }
}
  void
CaenSY4527::ComDeinit()
{
  int ret = CAENHV_DeinitSystem(fCaenCrateHandle);
  if(ret != CAENHV_OK)
    throw  CaenSY4527_except().CommunicationFailure(fCaenCrateHandle, "return value "+std::to_string(ret));
}

void
CaenSY4527::GetCrateMap()
{
  ushort nrslots, *nrchlist, *sernumlist;
  char *modellist,*descrlist;
  unsigned char *firmwaremin,*firmawaremax;

 int ret = CAENHV_GetCrateMap(fCaenCrateHandle,
 &nrslots,            //ushort *NrOfSlot,
 &nrchlist,           //ushort **NrofChList,
 &modellist,          //char **ModelList,
 &descrlist,          //char **DescriptionList,
 &sernumlist,         //ushort **SerNumList,
 &firmwaremin,        //uchar **FmwRelMinList,
 &firmawaremax);      //uchar **FmwRelMaxList);

 for(int i=0;i<nrslots;++i){
   std::cout
     <<"nrchlist    ["<<i<<"]'"<<nrchlist         [i] <<"'"<<std::endl
     <<"modellist   ["<<i<<"]'"<<modellist        [i] <<"'"<<std::endl
     <<"descrlist   ["<<i<<"]'"<<descrlist        [i] <<"'"<<std::endl
     <<"sernumlist  ["<<i<<"]'"<<sernumlist       [i] <<"'"<<std::endl
     <<"firmwaremin ["<<i<<"]'"<<int(firmwaremin  [i])<<"'"<<std::endl
     <<"firmawaremax["<<i<<"]'"<<int(firmawaremax [i])<<"'"<<std::endl
     <<std::endl;

 }
 delete[] nrchlist    ;/// must be dealocated by the user
 delete[] modellist   ;/// must be dealocated by the user
 delete[] descrlist   ;/// must be dealocated by the user
 delete[] sernumlist  ;/// must be dealocated by the user
 delete[] firmwaremin ;/// must be dealocated by the user
 delete[] firmawaremax;/// must be dealocated by the user
 if(ret != CAENHV_OK)
   throw  CaenSY4527_except().CommunicationFailure(fCaenCrateHandle, "return value "+std::to_string(ret));
}


  void
CaenSY4527::GetExecCommList() ///Get list of possible 
{

//  CAENHVLIB_API CAENHVRESULT  CAENHV_GetExecCommList(int handle,
//      ushort *NumComm, char **CommNameList);

}





