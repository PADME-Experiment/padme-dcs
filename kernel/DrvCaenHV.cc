#include "DrvCaenHV.h"   //in c file
#include"fwk/utlCommaDashListToVector.h"
#include <caenlib/CAENHVWrapper.h>
#include<iostream>

  DrvCaenHV_except&
DrvCaenHV_except::CAENWrapperRetStatus(int caenhandler,int retstatus, const std::string& add)
{ std::string a(CAENHV_GetError(caenhandler));
std::string error=(
retstatus==0     ? "Command wrapper correctly executed"                                            :
retstatus==1     ? "Error of operatived system"                                                    :
retstatus==2     ? "Write error in communication channel"                                          :
retstatus==3     ? "Read error in communication channel"                                           :
retstatus==4     ? "Time out in server communication"                                              :
retstatus==5     ? "Command Front End application is down"                                         :
retstatus==6     ? "Communication with system not yet connected by a Login command"                :
retstatus==7     ? "Communication with a not present board/slot"                                   :
retstatus==8     ? "Communication with RS232 not yet implemented"                                  :
retstatus==9     ? "User memory not sufficient"                                                    :
retstatus==10    ? "Value out of range"                                                            :
retstatus==11    ? "Execute command not yet implemented"                                           :
retstatus==12    ? "Get Property not yet implemented"                                              :
retstatus==13    ? "Set Property not yet implemented"                                              :
retstatus==14    ? "Property not found"                                                            :
retstatus==15    ? "Execute command not found"                                                     :
retstatus==16    ? "No System property"                                                            :
retstatus==17    ? "No get property"                                                               :
retstatus==18    ? "No set property"                                                               :
retstatus==19    ? "No execute command"                                                            :
retstatus==20    ? "Device configuration changed"                                                  :
retstatus==21    ? "Property of param not found"                                                   :
retstatus==22    ? "Param not found"                                                               :
retstatus==23    ? "No data present"                                                               :
retstatus==24    ? "Device already open"                                                           :
retstatus==25    ? "To Many devices opened"                                                        :
retstatus==26    ? "Function Parameter not valid"                                                  :
retstatus==27    ? "Function not available for the connected device"                               :
retstatus==0x1001? "Device already connected"                                                      :
retstatus==0x1002? "Device not connected"                                                          :
retstatus==0x1003? "Operating system error"                                                        :
retstatus==0x1004? "Login failed"                                                                  :
retstatus==0x1005? "Logout failed"                                                                 :
retstatus==0x1006? "Link type not supported"                                                       :
retstatus==0x1007? "Login failed for username/password ( SY4527 / SY5527 )"                        :
"Unknown");


  std::string str("CAENHVWrapper returned error ("+std::to_string(retstatus)+") : '" + a + "'  "+error);
  if(add.size()>0)str+="   "+add;

  switch (retstatus){
    case CAENHV_SYSERR               : throw DrvCaenHV_except::Except_SYSERR               (str) ;break;
    case CAENHV_WRITEERR             : throw DrvCaenHV_except::Except_WRITEERR             (str) ;break;
    case CAENHV_READERR              : throw DrvCaenHV_except::Except_READERR              (str) ;break;
    case CAENHV_TIMEERR              : throw DrvCaenHV_except::Except_TIMEERR              (str) ;break;
    case CAENHV_DOWN                 : throw DrvCaenHV_except::Except_DOWN                 (str) ;break;
    case CAENHV_NOTPRES              : throw DrvCaenHV_except::Except_NOTPRES              (str) ;break;
    case CAENHV_SLOTNOTPRES          : throw DrvCaenHV_except::Except_SLOTNOTPRES          (str) ;break;
    case CAENHV_NOSERIAL             : throw DrvCaenHV_except::Except_NOSERIAL             (str) ;break;
    case CAENHV_MEMORYFAULT          : throw DrvCaenHV_except::Except_MEMORYFAULT          (str) ;break;
    case CAENHV_OUTOFRANGE           : throw DrvCaenHV_except::Except_OUTOFRANGE           (str) ;break;
    case CAENHV_EXECCOMNOTIMPL       : throw DrvCaenHV_except::Except_EXECCOMNOTIMPL       (str) ;break;
    case CAENHV_GETPROPNOTIMPL       : throw DrvCaenHV_except::Except_GETPROPNOTIMPL       (str) ;break;
    case CAENHV_SETPROPNOTIMPL       : throw DrvCaenHV_except::Except_SETPROPNOTIMPL       (str) ;break;
    case CAENHV_PROPNOTFOUND         : throw DrvCaenHV_except::Except_PROPNOTFOUND         (str) ;break;
    case CAENHV_EXECNOTFOUND         : throw DrvCaenHV_except::Except_EXECNOTFOUND         (str) ;break;
    case CAENHV_NOTSYSPROP           : throw DrvCaenHV_except::Except_NOTSYSPROP           (str) ;break;
    case CAENHV_NOTGETPROP           : throw DrvCaenHV_except::Except_NOTGETPROP           (str) ;break;
    case CAENHV_NOTSETPROP           : throw DrvCaenHV_except::Except_NOTSETPROP           (str) ;break;
    case CAENHV_NOTEXECOMM           : throw DrvCaenHV_except::Except_NOTEXECOMM           (str) ;break;
    case CAENHV_SYSCONFCHANGE        : throw DrvCaenHV_except::Except_SYSCONFCHANGE        (str) ;break;
    case CAENHV_PARAMPROPNOTFOUND    : throw DrvCaenHV_except::Except_PARAMPROPNOTFOUND    (str) ;break;
    case CAENHV_PARAMNOTFOUND        : throw DrvCaenHV_except::Except_PARAMNOTFOUND        (str) ;break;
    case CAENHV_NODATA               : throw DrvCaenHV_except::Except_NODATA               (str) ;break;
    case CAENHV_DEVALREADYOPEN       : throw DrvCaenHV_except::Except_DEVALREADYOPEN       (str) ;break;
    case CAENHV_TOOMANYDEVICEOPEN    : throw DrvCaenHV_except::Except_TOOMANYDEVICEOPEN    (str) ;break;
    case CAENHV_INVALIDPARAMETER     : throw DrvCaenHV_except::Except_INVALIDPARAMETER     (str) ;break;
    case CAENHV_FUNCTIONNOTAVAILABLE : throw DrvCaenHV_except::Except_FUNCTIONNOTAVAILABLE (str) ;break;
    case CAENHV_SOCKETERROR          : throw DrvCaenHV_except::Except_SOCKETERROR          (str) ;break;
    case CAENHV_COMMUNICATIONERROR   : throw DrvCaenHV_except::Except_COMMUNICATIONERROR   (str) ;break;
    case CAENHV_NOTYETIMPLEMENTED    : throw DrvCaenHV_except::Except_NOTYETIMPLEMENTED    (str) ;break;
    case CAENHV_CONNECTED            : throw DrvCaenHV_except::Except_CONNECTED            (str) ;break;
    case CAENHV_NOTCONNECTED         : throw DrvCaenHV_except::Except_NOTCONNECTED         (str) ;break;
    case CAENHV_OS                   : throw DrvCaenHV_except::Except_OS                   (str) ;break;
    case CAENHV_LOGINFAILED          : throw DrvCaenHV_except::Except_LOGINFAILED          (str) ;break;
    case CAENHV_LOGOUTFAILED         : throw DrvCaenHV_except::Except_LOGOUTFAILED         (str) ;break;
    case CAENHV_LINKNOTSUPPORTED     : throw DrvCaenHV_except::Except_LINKNOTSUPPORTED     (str) ;break;
    case CAENHV_USERPASSFAILED       : throw DrvCaenHV_except::Except_USERPASSFAILED       (str) ;break;
  }
}














  int
DrvCaenHV::ComInit()
{
  CAENHVRESULT ret;
  int handle;
  CAENHV_SYSTEM_TYPE_t sys_type = (CAENHV_SYSTEM_TYPE_t) SY4527; // 0: SY1527, 2: SY4527
  int link_type = LINKTYPE_TCPIP;
  ret = CAENHV_InitSystem(sys_type, link_type, (void*)fIPAddress.c_str(), fUsername.c_str(), fPassword.c_str(), &handle);
  if(ret != CAENHV_OK){
    DrvCaenHV_except::CAENWrapperRetStatus(handle,ret,
        "IP = "+fIPAddress+"  user = "+fUsername+"  pass = "+fPassword);
  }
  return handle;
}

  void
DrvCaenHV::ComDeinit(int handle)
{
  int ret = CAENHV_DeinitSystem(handle);
  if(ret != CAENHV_OK)
    DrvCaenHV_except::CAENWrapperRetStatus(handle,ret);
}







  void
DrvCaenHV::AssertInit()
{
  INFO("DrvCaenHV::AssertInit()");
  //#warning CAEN ComInit
  fCaenCrateHandle=ComInit();
  AssertInitAllOwned();
  ProcessUpdateListTemp();
}
  void
DrvCaenHV::Finalize()
{
  this->VDeviceBase::Finalize();
  //#warning CAEN ComDeinit
  ComDeinit(fCaenCrateHandle );
  JoinThread();
}


void
DrvCaenHV::OnCycle(){
  std::this_thread::sleep_for(std::chrono::seconds(1));
  UpdateAll();
}


