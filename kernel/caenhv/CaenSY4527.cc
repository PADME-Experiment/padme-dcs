#include "CaenSY4527.h"   //in c file
#include <caenlib/CAENHVWrapper.h>
#include<iostream>
/*{{{*/
  CaenSY4527_except&
CaenSY4527_except::CAENWrapperRetStatus(int caenhandler,int retstatus, const std::string& add)
{ std::string a(CAENHV_GetError(caenhandler));
  std::string str("CAENHVWrapper returned error ("+std::to_string(retstatus)+") : '" + a + "'");
  if(add.size()>0)str+="\n"+add;

  throw  CaenSY4527_except::Except_OK               (str) ;
  switch (retstatus){
    case CAENHV_SYSERR               : throw CaenSY4527_except::Except_SYSERR               (str) ;break;
    case CAENHV_WRITEERR             : throw CaenSY4527_except::Except_WRITEERR             (str) ;break;
    case CAENHV_READERR              : throw CaenSY4527_except::Except_READERR              (str) ;break;
    case CAENHV_TIMEERR              : throw CaenSY4527_except::Except_TIMEERR              (str) ;break;
    case CAENHV_DOWN                 : throw CaenSY4527_except::Except_DOWN                 (str) ;break;
    case CAENHV_NOTPRES              : throw CaenSY4527_except::Except_NOTPRES              (str) ;break;
    case CAENHV_SLOTNOTPRES          : throw CaenSY4527_except::Except_SLOTNOTPRES          (str) ;break;
    case CAENHV_NOSERIAL             : throw CaenSY4527_except::Except_NOSERIAL             (str) ;break;
    case CAENHV_MEMORYFAULT          : throw CaenSY4527_except::Except_MEMORYFAULT          (str) ;break;
    case CAENHV_OUTOFRANGE           : throw CaenSY4527_except::Except_OUTOFRANGE           (str) ;break;
    case CAENHV_EXECCOMNOTIMPL       : throw CaenSY4527_except::Except_EXECCOMNOTIMPL       (str) ;break;
    case CAENHV_GETPROPNOTIMPL       : throw CaenSY4527_except::Except_GETPROPNOTIMPL       (str) ;break;
    case CAENHV_SETPROPNOTIMPL       : throw CaenSY4527_except::Except_SETPROPNOTIMPL       (str) ;break;
    case CAENHV_PROPNOTFOUND         : throw CaenSY4527_except::Except_PROPNOTFOUND         (str) ;break;
    case CAENHV_EXECNOTFOUND         : throw CaenSY4527_except::Except_EXECNOTFOUND         (str) ;break;
    case CAENHV_NOTSYSPROP           : throw CaenSY4527_except::Except_NOTSYSPROP           (str) ;break;
    case CAENHV_NOTGETPROP           : throw CaenSY4527_except::Except_NOTGETPROP           (str) ;break;
    case CAENHV_NOTSETPROP           : throw CaenSY4527_except::Except_NOTSETPROP           (str) ;break;
    case CAENHV_NOTEXECOMM           : throw CaenSY4527_except::Except_NOTEXECOMM           (str) ;break;
    case CAENHV_SYSCONFCHANGE        : throw CaenSY4527_except::Except_SYSCONFCHANGE        (str) ;break;
    case CAENHV_PARAMPROPNOTFOUND    : throw CaenSY4527_except::Except_PARAMPROPNOTFOUND    (str) ;break;
    case CAENHV_PARAMNOTFOUND        : throw CaenSY4527_except::Except_PARAMNOTFOUND        (str) ;break;
    case CAENHV_NODATA               : throw CaenSY4527_except::Except_NODATA               (str) ;break;
    case CAENHV_DEVALREADYOPEN       : throw CaenSY4527_except::Except_DEVALREADYOPEN       (str) ;break;
    case CAENHV_TOOMANYDEVICEOPEN    : throw CaenSY4527_except::Except_TOOMANYDEVICEOPEN    (str) ;break;
    case CAENHV_INVALIDPARAMETER     : throw CaenSY4527_except::Except_INVALIDPARAMETER     (str) ;break;
    case CAENHV_FUNCTIONNOTAVAILABLE : throw CaenSY4527_except::Except_FUNCTIONNOTAVAILABLE (str) ;break;
    case CAENHV_SOCKETERROR          : throw CaenSY4527_except::Except_SOCKETERROR          (str) ;break;
    case CAENHV_COMMUNICATIONERROR   : throw CaenSY4527_except::Except_COMMUNICATIONERROR   (str) ;break;
    case CAENHV_NOTYETIMPLEMENTED    : throw CaenSY4527_except::Except_NOTYETIMPLEMENTED    (str) ;break;
    case CAENHV_CONNECTED            : throw CaenSY4527_except::Except_CONNECTED            (str) ;break;
    case CAENHV_NOTCONNECTED         : throw CaenSY4527_except::Except_NOTCONNECTED         (str) ;break;
    case CAENHV_OS                   : throw CaenSY4527_except::Except_OS                   (str) ;break;
    case CAENHV_LOGINFAILED          : throw CaenSY4527_except::Except_LOGINFAILED          (str) ;break;
    case CAENHV_LOGOUTFAILED         : throw CaenSY4527_except::Except_LOGOUTFAILED         (str) ;break;
    case CAENHV_LINKNOTSUPPORTED     : throw CaenSY4527_except::Except_LINKNOTSUPPORTED     (str) ;break;
    case CAENHV_USERPASSFAILED       : throw CaenSY4527_except::Except_USERPASSFAILED       (str) ;break;
  }
}






/*}}}*/








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
    CaenSY4527_except::CAENWrapperRetStatus(fCaenCrateHandle,ret,
        "IP = "+ipaddr+"\nuser = "+user+"\npass = "+pass);
  }
}
  void
CaenSY4527::ComDeinit()
{
  int ret = CAENHV_DeinitSystem(fCaenCrateHandle);
  if(ret != CAENHV_OK)
    CaenSY4527_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
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

  if(ret != CAENHV_OK)
    CaenSY4527_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);

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

  std::cerr<<"bef del "<<__FILE__<<__LINE__<<__func__<<std::endl;
  delete[] nrchlist    ;/// must be dealocated by the user
  delete[] modellist   ;/// must be dealocated by the user
  delete[] descrlist   ;/// must be dealocated by the user
  delete[] sernumlist  ;/// must be dealocated by the user
  delete[] firmwaremin ;/// must be dealocated by the user
  delete[] firmawaremax;/// must be dealocated by the user
}


  void
CaenSY4527::GetExecCommList() ///Get list of possible 
{
  ushort numcom;
  char*comnamelist;

  int ret=CAENHV_GetExecCommList(fCaenCrateHandle,&numcom,&comnamelist);
  if(ret!=CAENHV_OK)
    CaenSY4527_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);
  std::string tmp;
  for(int i=0;i<numcom;++i){
    tmp=comnamelist[tmp.size()];
    std::cout<<tmp<<"   ";
  } std::cout<<std::endl;

  delete[] comnamelist;

}


  void
CaenSY4527::GetSysPropList() ///Get list of possible 
{
  ushort numcom;
  char*comnamelist;

  int ret=CAENHV_GetSysPropList(fCaenCrateHandle,&numcom,&comnamelist);
  if(ret!=CAENHV_OK)
    CaenSY4527_except::CAENWrapperRetStatus(fCaenCrateHandle,ret);

  std::string tmp;
  for(int i=0;i<numcom;++i){
    tmp=comnamelist[tmp.size()];
    std::cout<<tmp<<"   ";
  } std::cout<<std::endl;

  delete[] comnamelist;

}





