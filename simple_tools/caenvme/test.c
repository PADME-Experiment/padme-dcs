extern "C"{
#include"V8100.h"
}
#include<iostream>
#include <unistd.h>


int main(int argc, char *argv[]){
  if(argc!=1){std::cerr<< "synopsis: "<<argv[0]<<"  <HOSTNAME/IP>"<<std::endl;return 1;}
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
    //V8100_mon_stat(&handler, UINT8 ch_id, V8100_channel_status *value, CMD_ERROR_CODE *error_code);
    //V8100_set_vset(&handler, UINT8 ch_id, float value , CMD_ERROR_CODE *error_code);
    //V8100_set_iset(&handler, UINT8 ch_id, float value , CMD_ERROR_CODE *error_code);
    //V8100_set_ovp (&handler, UINT8 ch_id, ui8, CMD_ERROR_CODE *error_code);
    //V8100_set_uvp (&handler, UINT8 ch_id, ui8, CMD_ERROR_CODE *error_code);
    std::cout<<std::endl;
    std::cout<<std::endl;
  sleep(100);
  }


  V8100_set_off(&handler,&err);
  V8100_close(&handler);
  return 0;
}



// Crate monitor methods
DLL_API BOOL V8100_mon_crname ( V8100_data* p_data, char *value, int value_size, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_numch  ( V8100_data* p_data, UINT8 *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_psfrel ( V8100_data* p_data, char *value, int value_size, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_pstemp ( V8100_data* p_data, float *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_pssnum ( V8100_data* p_data, UINT32 *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_fansp  ( V8100_data* p_data, V8100_FAN_SPEED_SET *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_fan1   ( V8100_data* p_data, UINT32 *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_fan2   ( V8100_data* p_data, UINT32 *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_fan3   ( V8100_data* p_data, UINT32 *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_fufrel ( V8100_data* p_data, char *value, int value_size, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_futemp ( V8100_data* p_data, float *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_fusnum ( V8100_data* p_data, UINT32 *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_crst   ( V8100_data* p_data, V8100_crate_status *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_vpmax  ( V8100_data* p_data, float *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_vpmin  ( V8100_data* p_data, float *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_rs232br( V8100_data* p_data, V8100_RS232_BITRATE *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_canbr  ( V8100_data* p_data, V8100_CANBUS_BITRATE *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_canadd ( V8100_data* p_data, UINT8 *value, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_ipadd  ( V8100_data* p_data, char *value, int value_size, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_ipmsk  ( V8100_data* p_data, char *value, int value_size, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_ipgtw  ( V8100_data* p_data, char *value, int value_size, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_mon_macadd ( V8100_data* p_data, char *value, int value_size, CMD_ERROR_CODE *error_code);

// Crate set methods
DLL_API BOOL V8100_set_on( V8100_data* p_data, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_set_off( V8100_data* p_data, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_set_sysr( V8100_data* p_data, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_set_clr( V8100_data* p_data, CMD_ERROR_CODE *error_code);
DLL_API BOOL V8100_set_fansp( V8100_data* p_data, V8100_FAN_SPEED_SET value, CMD_ERROR_CODE *error_code);
