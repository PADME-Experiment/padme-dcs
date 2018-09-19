
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
  V8100_channel_status chan_status;

  for(UINT8 ch=0;ch<3;++ch){
    std::cout<<int(ch)<<std::endl;
    ret_bool=V8100_mon_name(&handler, ch, chararr, length, &err); std::cout<<"mon_name  "<<chararr<<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_vset(&handler, ch, &f             , &err); std::cout<<"mon_vset  "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_vmin(&handler, ch, &f             , &err); std::cout<<"mon_vmin  "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_vmax(&handler, ch, &f             , &err); std::cout<<"mon_vmax  "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_vres(&handler, ch, &f             , &err); std::cout<<"mon_vres  "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_ovp (&handler, ch, &f             , &err); std::cout<<"mon_ovp   "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_uvp (&handler, ch, &f             , &err); std::cout<<"mon_uvp   "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_vmon(&handler, ch, &f             , &err); std::cout<<"mon_vmon  "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_iset(&handler, ch, &f             , &err); std::cout<<"mon_iset  "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_imin(&handler, ch, &f             , &err); std::cout<<"mon_imin  "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_imax(&handler, ch, &f             , &err); std::cout<<"mon_imax  "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_ires(&handler, ch, &f             , &err); std::cout<<"mon_ires  "<<f      <<"  "<<ret_bool<<std::endl;
    ret_bool=V8100_mon_imon(&handler, ch, &f             , &err); std::cout<<"mon_imon  "<<f      <<"  "<<ret_bool<<std::endl;
    //ret_bool=V8100_mon_stat(&handler, ch, &chan_status,           , &err); std::cout<<"mon_stat  "<<chan_status<<"  "<<ret_bool<<std::endl;
    std::cout<<std::endl;
  }
    std::cout<<std::endl;

  V8100_RS232_BITRATE  rs_bitrate;
  V8100_CANBUS_BITRATE can_bitrate;
  V8100_FAN_SPEED_SET  fanspeed;
  V8100_crate_status crate_stat;

  ret_bool=V8100_mon_crname ( &handler, chararr,length, &err);std::cout<<"mon_crname   "<<chararr       <<std::endl;
  ret_bool=V8100_mon_numch  ( &handler, &ui8          , &err);std::cout<<"mon_numch    "<<ui8          <<std::endl;
  ret_bool=V8100_mon_psfrel ( &handler, chararr,length, &err);std::cout<<"mon_psfrel   "<<chararr       <<std::endl;
  ret_bool=V8100_mon_pstemp ( &handler, &f            , &err);std::cout<<"mon_pstemp   "<<f            <<std::endl;
  ret_bool=V8100_mon_pssnum ( &handler, &ui32         , &err);std::cout<<"mon_pssnum   "<<ui32         <<std::endl;
  ret_bool=V8100_mon_fansp  ( &handler, &fanspeed     , &err);std::cout<<"mon_fansp    "<<fanspeed     <<std::endl;
  ret_bool=V8100_mon_fan1   ( &handler, &ui32         , &err);std::cout<<"mon_fan1     "<<ui32         <<std::endl;
  ret_bool=V8100_mon_fan2   ( &handler, &ui32         , &err);std::cout<<"mon_fan2     "<<ui32         <<std::endl;
  ret_bool=V8100_mon_fan3   ( &handler, &ui32         , &err);std::cout<<"mon_fan3     "<<ui32         <<std::endl;
  ret_bool=V8100_mon_fufrel ( &handler, chararr,length, &err);std::cout<<"mon_fufrel   "<<chararr       <<std::endl;
  ret_bool=V8100_mon_futemp ( &handler, &f            , &err);std::cout<<"mon_futemp   "<<f            <<std::endl;
  ret_bool=V8100_mon_fusnum ( &handler, &ui32         , &err);std::cout<<"mon_fusnum   "<<ui32         <<std::endl;
  //ret_bool=V8100_mon_crst   ( &handler, &crate_stat   , &err);std::cout<<"mon_crst     "<<crate_stat   <<std::endl;
  ret_bool=V8100_mon_vpmax  ( &handler, &f            , &err);std::cout<<"mon_vpmax    "<<f            <<std::endl;
  ret_bool=V8100_mon_vpmin  ( &handler, &f            , &err);std::cout<<"mon_vpmin    "<<f            <<std::endl;
  ret_bool=V8100_mon_rs232br( &handler, &rs_bitrate   , &err);std::cout<<"mon_rs232br  "<<rs_bitrate   <<std::endl;
  ret_bool=V8100_mon_canbr  ( &handler, &can_bitrate  , &err);std::cout<<"mon_canbr    "<<can_bitrate  <<std::endl;
  ret_bool=V8100_mon_canadd ( &handler, &ui8          , &err);std::cout<<"mon_canadd   "<<ui8          <<std::endl;
  ret_bool=V8100_mon_ipadd  ( &handler, chararr,length, &err);std::cout<<"mon_ipadd    "<<chararr       <<std::endl;
  ret_bool=V8100_mon_ipmsk  ( &handler, chararr,length, &err);std::cout<<"mon_ipmsk    "<<chararr       <<std::endl;
  ret_bool=V8100_mon_ipgtw  ( &handler, chararr,length, &err);std::cout<<"mon_ipgtw    "<<chararr       <<std::endl;
  ret_bool=V8100_mon_macadd ( &handler, chararr,length, &err);std::cout<<"mon_macadd   "<<chararr       <<std::endl;






  V8100_close(&handler);
  return 0;
}

