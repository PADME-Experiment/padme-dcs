#include "HVcontrol.h"


#include <signal.h>
#ifdef UNIX
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#endif
#include <string>
#include <vector>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include "CAENHVWrapper.h"
#include <ctype.h>
#include <cmath>


int main(int argc, char *argv[]){
  for(int i=0;i<7;++i){gListOfChannels.push_back(i);}


  int handle;
  if(Connect(handle)!=0)return 99;

  //// Pares options
  //CAENHV_SYSTEM_TYPE_t tmp_sys_type;
  //int tmp_link_type; 
  //std::string tmp_address;
  //int slot;
  //unsigned short tmpCh;
  //int channels_on[CH_IN_MATRIX];
  //for(int im=0;im<CH_IN_MATRIX;im++) channels_on[im] = 0;

  /*
   * Options needed:
   * - SetV0 for all the channels H
   * - GetVMon for all the channels V
   * - GetIMon for all the channels I
   * - GetZ U/I all the channels Z
   * - GetStatus RUp, RDn, On, Off S
   * these options should return space separated list
   */

  int c;
  while((c = getopt(argc, argv, "10H:VIZSt:l:a:s:c:A:h")) != -1){
    switch(c){
      case '0':return SetPower(handle,0); break;
      case '1':return SetPower(handle,1); break;
      case 'H':
        unsigned int voltageToBeSet;
        if ( sscanf(optarg,"%d",&voltageToBeSet) != 1 ) {
          fprintf (stderr, "Error while processing option '-H'. Wrong parameter '%s'.\n", optarg);
          exit(1);
        }else{return SetVoltage(handle,voltageToBeSet);}
        break;
      case 'V':return GetVMon(handle);break;
      case 'I':return GetIMon(handle);break;
      case 'Z':return GetZ(handle);break;
      case 'S':return GetStatus(handle);break;

//      case 't':
//        if ( sscanf(optarg,"%d",&tmp_sys_type) != 1 ) {
//          fprintf (stderr, "Error while processing option '-t'. Wrong parameter '%s'.\n", optarg);
//          exit(1);
//        }
//        fprintf(stdout,"System type: %d\n", tmp_sys_type);
//        sys_type = (CAENHV_SYSTEM_TYPE_t)tmp_sys_type; 
//        break;
//
//      case 'l':
//        if ( sscanf(optarg,"%d",&tmp_link_type) != 1 ) {
//          fprintf (stderr, "Error while processing option '-l'. Wrong parameter '%s'.\n", optarg);
//          exit(1);
//        }
//        fprintf(stdout,"Link type: %d\n", tmp_link_type);
//        link_type = tmp_link_type;
//        break;
//
//      case 'a':
//        if ( sscanf(optarg,"%d",tmp_address.c_str()) != 1 ) {
//          fprintf (stderr, "Error while processing option '-a'. Wrong parameter '%s'.\n", optarg);
//          exit(1);
//        }
//        fprintf(stdout,"Link type: %d\n", tmp_address.c_str());
//        address = tmp_address;
//        break;
//
//      case 's':
//        if ( sscanf(optarg,"%d",&slot) != 1 ) {
//          fprintf (stderr, "Error while processing option '-s'. Wrong parameter '%s'.\n", optarg);
//          exit(1);
//        }
//        fprintf(stdout,"Slot n.: %d\n", slot);
//        break;
//
//      case 'c':
//        if ( sscanf(optarg,"%d",&tmpCh) != 1 ) {
//          fprintf (stderr, "Error while processing option '-c'. Wrong parameter '%s'.\n", optarg);
//          exit(1);
//        }
//        if(tmpCh < 0){
//          fprintf (stderr, "Error while processing option '-c'. Required channel %d (must be >=0).\nChannel %d will NOT be added to the list.\n", tmpCh);
//        }
//        fprintf(stdout,"Channel %d will be added to the list\n", tmpCh);
//        channels_on[tmpCh] = 1;
//        NrOfCh++;
//        break;
//
//      case 'A':
//        fprintf(stdout,"All the channels from 0 to 32 will be turned ON.\n");
//        NrOfCh = 0; // if option -c is used, reset NrOfCh
//        for(int iA=0;iA<CH_IN_MATRIX;iA++){
//          channels_on[iA] = 1;
//          NrOfCh++; 
//        }
//        break;
//
//      case 'HV':
//        if ( sscanf(optarg,"%d",&HV) != 1 ) {
//          fprintf (stderr, "Error while processing option '-HV'. Wrong parameter '%s'.\n", optarg);
//          exit(1);
//        }
//        if(HV < 0){
//          fprintf (stderr, "Error while processing option '-HV'. Required voltage %d (must be >=0).\n");
//          exit(1);
//        }
//        fprintf(stdout,"HV = %f\n", HV);
//        break;

      case 'h':
        fprintf(stderr,"./PadmeHV [options]\n\n");
        fprintf(stderr,"\t-0: Switch OFF\n");
        fprintf(stderr,"\t-1: Switch ON\n");
        fprintf(stderr,"\t-H: Set voltage\n");
        fprintf(stderr,"\t-V: Read voltage\n");
        fprintf(stderr,"\t-I: Read current\n");
        fprintf(stderr,"\t-Z: Read impedance\n");
        fprintf(stderr,"\t-S: Read status\n");

        //fprintf(stdout,"\t-t: define system type\n");
        //fprintf(stdout,"\t-l: define link type\n");
        //fprintf(stdout,"\t-a: define link address\n");
        //fprintf(stdout,"\t-s: define the slot\n");
        //fprintf(stdout,"\t-c: define a channel to be used\n");
        //fprintf(stdout,"\t-A: All channels will be used\n");
        //fprintf(stdout,"\t-HV: set the High Votage value in Volts\n");
        //fprintf(stdout,"\t-: \n");
        //fprintf(stdout,"\t-: \n");
        //fprintf(stdout,"\t-h: show this help and exit\n\n");
        return(0);
        break;

      default:
        abort();

    }

  }
  if(Disconnect(handle)!=0)return 99;


//  std::vector<int> Slot_Ch(NrOfCh);
//  for(nch=0;nch<CH_IN_MATRIX;nch++){
//    if(channels_on[nch]){
//      Slot_Ch[nch] = 100*slot + nch;
//    }
//  }
//  std::vector<unsigned short int> listaCh(NrOfCh);
//  std::vector<int> fPwList(NrOfCh);
//  std::vector<int> fStatusList(NrOfCh);
//  std::vector<float> fVoltList(NrOfCh);
//  std::vector<float> fIList(NrOfCh);
//  std::vector<unsigned short int> check_ch(NrOfCh);
//  for(nch=0;nch<NrOfCh;nch++) check_ch[nch] = 0;
//
//
//
//
//  // CRATE MAP //
//
//  //ret = CAENHV_GetCrateMap(sysHndl,&nSlot,&);
//
//  // end of crate map //
//
//
//  // GET CHANNEL NAME //
//
//  for(nch=0;nch<NrOfCh;nch++){
//
//    listaCh[nch] = Slot_Ch[nch]%100;
//  }
//
//  listNameCh = new char[NrOfCh*MAX_CH_NAME];
//  for(nch=0;nch<NrOfCh;nch++){
//
//    ret = CAENHV_GetChName(sysHndl, (Slot_Ch[nch]/100), NrOfCh, (unsigned short int*)listaCh.begin(), listNameCh);
//
//    if(ret != CAENHV_OK){
//
//      free(listNameCh);
//      printf("ERROR!!! ===> CAENHV_GetChName: %s (num. %d)\n\n", CAENHV_GetError(sysHndl), ret);
//
//      return 0; 
//    }
//  }
//
//  // end of channel name //
//
//
//  // GET CHANNEL STATUS, VOLTAGE AND CURRENT //
//
//  check_HV(NrOfCh,sysHndl,listaCh,listNameCh,Slot_Ch,fStatusList,fVoltList,fIList,1);
//
//  // check that is off (if not turn the channel off) and that V and I are 0
//  int AllChOff = 1;
//  int cycle = 0;
//  do{
//    for(nch=0;nch<NrOfCh;nch++){
//
//      /*   ret = CAENHV_GetChParam(sysHndl, Slot_Ch[nch]/100, "Pw", NrOfCh, listaCh, &fPwList);
//
//           if(fPwList[nch]) printf("Channel %d is ON\n", nch);
//           else printf("Channel %d is OFF\n", nch);
//           */
//      if((fVoltList[nch]>2.) || (fIList[nch]>1.)){ 
//
//        if(0/*channel is on*/){ // channel is on => turn it off
//
//          AllChOff = 0;
//
//          ret = CAENHV_SetChParam(sysHndl, Slot_Ch[nch]/100, Pw, nch, listaCh, &OFF);
//
//          printf("Turning off channel n. %3d: %10s\n", listaCh[nch],listNameCh[nch]);
//
//        }else{ // channel is already off!
//
//          printf("WARNING - Channel n. %3d: %10s is already OFF, but CURRENT/VOLTAGE ARE NON ZERO!!!\n", listaCh[nch],listNameCh[nch]);
//        }
//
//      }
//
//    } // end of cycle on channels
//
//    if(!AllChOff){
//
//      printf("Wait %d seconds\n",(3*(waitDWn-1)/2.));
//      sleep(3*(waitDWn-1)/2.);
//
//      cycle++;
//    }
//
//  }while(AllChOff==0);
//
//
//  // end of channel name and VMon //
//
//
//  // SET V0 TO INPUT VALUE //
//  /*
//     printf("\n\n===> SET HV = %7.2f V\n",HV);
//     char V0Set[30] = "V0Set";
//     for(nch=0;nch<NrOfCh;nch++){
//
//     int slot = Slot_Ch[nch]/100;
//
//     if((Slot_Ch[nch]/100==slot) && (nch>0)){
//  // do nothing
//  } else {
//  ret = CAENHV_SetChParam(sysHndl, Slot_Ch[nch]/100, V0Set, NrOfCh, listaCh, &HV);
//
//  printf("CAENHV_SetChParam: %s %s (num. %d)\n", V0Set,CAENHV_GetError(sysHndl), ret);
//  }
//  }
//
//
//  // TURN HV ON //
//
//  printf("\n\n===> TURNING HV ON\n");
//  for(nch=0;nch<NrOfCh;nch++){
//
//  int slot = Slot_Ch[nch]/100;
//
//  if((Slot_Ch[nch]/100==slot) && (nch>0)){
//  // do nothing
//  } else {
//  ret = CAENHV_SetChParam(sysHndl, Slot_Ch[nch]/100, Pw, NrOfCh, listaCh, &ON);
//
//  printf("CAENHV_SetChParam: %s %s (num. %d)\n", Pw,CAENHV_GetError(sysHndl), ret);
//  }
//  }
//
//  // wait channels reach the HV and then read values
//  printf("\n\nwaiting %2d seconds\n\n", waitRUp);
//  sleep(waitRUp);
//
//  check_HV(NrOfCh,sysHndl,listaCh,listNameCh,Slot_Ch,fStatusList,fVoltList,fIList,1);
//
//
//  // TURN HV OFF
//
//  printf("\n\n===> TURNING HV OFF\n");
//  for(nch=0;nch<NrOfCh;nch++){
//
//  int slot = Slot_Ch[nch]/100;
//
//  if((Slot_Ch[nch]/100==slot) && (nch>0)){
//  // do nothing
//  } else {
//  ret = CAENHV_SetChParam(sysHndl, Slot_Ch[nch]/100, Pw, NrOfCh, listaCh, &OFF);
//
//  printf("CAENHV_SetChParam: %s %s (num. %d)\n", Pw,CAENHV_GetError(sysHndl), ret);
//  }
//  }
//
//  // wait channels reach 0 V and then read values
//  printf("\n\nwaiting %2d seconds\n\n", waitDWn);
//  sleep(waitDWn);
//
//  check_HV(NrOfCh,sysHndl,listaCh,listNameCh,Slot_Ch,fStatusList,fVoltList,fIList,1);
//
//
//  // end of V0Set //
//  */
//
//  free(listNameCh);
//  fflush(stdout);  
  return 0;
}

int Connect(int& handle){
  CAENHVRESULT ret;
  // Default system settings
  CAENHV_SYSTEM_TYPE_t sys_type =  (CAENHV_SYSTEM_TYPE_t)2; // 0: SY1527, 2: SY4527
  int link_type = 0; // TCP/IP
  std::string address = "192.168.0.1"; // SY1527: "10.10.10.3", SY4527: "192.168.0.1"

  ret = CAENHV_InitSystem(sys_type, link_type, (void*)address.c_str(), "admin", "admin", &handle);
  if(ret != CAENHV_OK){
    fprintf(stderr,"ERROR!!! ===> CAENHV_InitSystem: %s (num. %d)\n\n", CAENHV_GetError(handle), ret);
    return 1;
  }else{
    fprintf(stderr,"\n===> CAENHV_InitSystem: %s (num. %d)\n\n\n", CAENHV_GetError(handle), ret);
  }
  return 0;
}

int Disconnect(int handle){
  CAENHVRESULT ret;
  ret = CAENHV_DeinitSystem(handle);
  if(ret == CAENHV_OK){
    fprintf(stderr,"\n\n===> CAENHV_DeinitSystem: Connection closed (num. %d)\n\n", ret);
    return 1;
  }
  else fprintf(stderr,"\n\nERROR!!! ===> CAENHV_DeinitSystem: %s (num. %d)\n\n", CAENHV_GetError(handle), ret);
  return 0;
}

int SetPower(int handle,int pw){
  CAENHVRESULT res;
  if(
      (res=CAENHV_SetChParam(
        handle, 0, "Pw", gListOfChannels.size(), &gListOfChannels[0],
        &(std::vector<unsigned int>(gListOfChannels.size(),pw)[0]))) != CAENHV_OK){
    fprintf(stderr,", CAENHV_GetChParam: %s (num. %d) - ERROR!!!\n\n", CAENHV_GetError(handle), res);
    return 99;
  }
  return 0;
}

int SetVoltage(int handle,unsigned int voltageToBeSet){
  CAENHVRESULT res;
  if(
      (res=CAENHV_SetChParam(
        handle, 0, "V0Set", gListOfChannels.size(), &gListOfChannels[0],
        &(std::vector<float>(gListOfChannels.size(),voltageToBeSet)[0]))) != CAENHV_OK){
    fprintf(stderr,", CAENHV_GetChParam: %s (num. %d) - ERROR!!!\n\n", CAENHV_GetError(handle), res);
    return 99;
  }
  return 0;
}

int GetZ(int handle){
  CAENHVRESULT res;
  float IStatuslist[gListOfChannels.size()];
  float VStatuslist[gListOfChannels.size()];
  if(
      (res=CAENHV_GetChParam(handle, 0, "IMon", gListOfChannels.size(), &gListOfChannels[0], IStatuslist)) != CAENHV_OK ||
      (res=CAENHV_GetChParam(handle, 0, "VMon", gListOfChannels.size(), &gListOfChannels[0], VStatuslist)) != CAENHV_OK){
    fprintf(stderr,", CAENHV_GetChParam: %s (num. %d) - ERROR!!!\n\n", CAENHV_GetError(handle), res);
    return 99;
  }else{
    for(int nn = 0; nn < gListOfChannels.size(); nn++) {
      printf("%f ",VStatuslist[nn]/    (floor(10*IStatuslist[nn])/10)    );
    }
    printf("\n");
  }
  return 0;
}

int GetIMon(int handle){
  CAENHVRESULT res;
  float Statuslist[gListOfChannels.size()];
  res = CAENHV_GetChParam(handle, 0, "IMon", gListOfChannels.size(), &gListOfChannels[0], Statuslist);
  if(res != CAENHV_OK){
    fprintf(stderr,", CAENHV_GetChParam: %s (num. %d) - ERROR!!!\n\n", CAENHV_GetError(handle), res);
    return 99;
  }else{
    for(int nn = 0; nn < gListOfChannels.size(); nn++) {
      printf("%f ",(floor(10*Statuslist[nn])/10));
    }
    printf("\n");
  }
  return 0;
}

int GetVMon(int handle){
  CAENHVRESULT res;
  float Statuslist[gListOfChannels.size()];
  res = CAENHV_GetChParam(handle, 0, "VMon", gListOfChannels.size(), &gListOfChannels[0], Statuslist);
  if(res != CAENHV_OK){
    fprintf(stderr,", CAENHV_GetChParam: %s (num. %d) - ERROR!!!\n\n", CAENHV_GetError(handle), res);
    return 99;
  }else{
    for(int nn = 0; nn < gListOfChannels.size(); nn++) {
      printf("%f ",Statuslist[nn]);
    }
    printf("\n");
  }
  return 0;
}

int GetStatus(int handle){
  CAENHVRESULT res;
  unsigned int Statuslist[gListOfChannels.size()];
  res = CAENHV_GetChParam(handle, 0, "Status", gListOfChannels.size(), &gListOfChannels[0], Statuslist);
  if(res != CAENHV_OK){
    fprintf(stderr,", CAENHV_GetChParam: %s (num. %d) - ERROR!!!\n\n", CAENHV_GetError(handle), res);
    return 99;
  }else{
    for(int nn = 0; nn < gListOfChannels.size(); nn++) {
      // Get Status
      //if(print) printf(", slot: %2d, %12d: ", slot_ch[nn]/100, Statuslist[nn]);
      if (Statuslist[nn] ==    0) printf("Off ");
      else if (Statuslist[nn] ==    1) printf("On  ");
      else if (Statuslist[nn] & 6 !=    0) printf("Rumping ");
      else printf("else ");
      //if (Statuslist[nn] &     1) printf("On  ");	else printf("Off ");	//OK
      //if (Statuslist[nn] &     2) printf("RUp ");	else printf("");	//?
      //if (Statuslist[nn] &     4) printf("RDw ");	else printf("");	//OK
      //if (Statuslist[nn] &     8) printf("OvC ");	else printf("");	//?
      //if (Statuslist[nn] &    16) printf("OvV ");	else printf("");	//?
      //if (Statuslist[nn] &    32) printf("UnV ");	else printf("");	//OK
      //if (Statuslist[nn] &    64) printf("ExtTr ");	else printf("");	//OK
      //if (Statuslist[nn] &   128) printf("MaxV ");	else printf("");	//?
      //if (Statuslist[nn] &   256) printf("ExtDis ");	else printf("");
      //if (Statuslist[nn] &   512) printf("IntTr ");	else printf("");
      //if (Statuslist[nn] &  1024) printf("1024 ");	else printf("");
      //if (Statuslist[nn] &  2048) printf("2048 ");	else printf("");
    }
    printf("\n");
  }
  return 0;
}





//  int check_HV(unsigned short nr_of_ch, int Hndl, unsigned short* listach, char (*chname)[MAX_CH_NAME], int* slot_ch, int *Statuslist, float* Vlist, float* Ilist, int print){
//
//    int nn;
//    CAENHVRESULT res;
//    //char VMon[5] = "VMon";
//    //res = CAENHV_GetChParam(Hndl, 0, VMon, nr_of_ch, listach, Vlist);
//
//    for(nn = 0; nn < nr_of_ch; nn++) {
//      printf("Channel n. %3d: %10s", listach[nn],chname[nn]);
//
//      // Get Status
//      res = CAENHV_GetChParam(Hndl, slot_ch[nn]/100, "Status", nr_of_ch, listach, Statuslist);
//      if(res != CAENHV_OK){
//        printf(", CAENHV_GetChParam: %s (num. %d) - ERROR!!!\n\n", CAENHV_GetError(Hndl), res);
//      }else{
//        if(print) printf(", slot: %2d, %12d: ", slot_ch[nn]/100, Statuslist[nn]);
//        if (Statuslist[nn] &     1) printf("On  ");	else printf("Off ");	//OK
//        if (Statuslist[nn] &     2) printf("RUp ");	else printf("    ");	//?
//        if (Statuslist[nn] &     4) printf("RDw ");	else printf("    ");	//OK
//        if (Statuslist[nn] &     8) printf("OvC ");	else printf("    ");	//?
//        if (Statuslist[nn] &    16) printf("OvV ");	else printf("    ");	//?
//        if (Statuslist[nn] &    32) printf("UnV ");	else printf("    ");	//OK
//        if (Statuslist[nn] &    64) printf("ExtTr ");	else printf("      ");	//OK
//        if (Statuslist[nn] &   128) printf("MaxV ");	else printf("     ");	//?
//        if (Statuslist[nn] &   256) printf("ExtDis ");	else printf("       ");
//        if (Statuslist[nn] &   512) printf("IntTr ");	else printf("      ");
//        if (Statuslist[nn] &  1024) printf("1024 ");	else printf("     ");
//        if (Statuslist[nn] &  2048) printf("2048 ");	else printf("     ");
//
//      }
//
//      // Get VMon
//      res = CAENHV_GetChParam(Hndl, slot_ch[nn]/100, VMon, nr_of_ch, listach, Vlist);
//      if(res != CAENHV_OK){
//        printf(", CAENHV_GetChParam: %s (num. %d) - ERROR!!!\n\n", CAENHV_GetError(Hndl), res);
//      }else{
//        if(print) printf(", %s: %7.2f V", VMon, Vlist[nn]);
//      }
//
//      // Get IMon
//      res = CAENHV_GetChParam(Hndl, slot_ch[nn]/100, IMon, nr_of_ch, listach, Ilist);
//      if(res != CAENHV_OK){
//        printf(", CAENHV_GetChParam: %s (num. %d) - ERROR!!!\n\n", CAENHV_GetError(Hndl), res);
//      }else{
//        if(print) printf(", %s: %6.1f uA\n", IMon, Ilist[nn]);
//      }
//
//    }
//
//
//    fflush(stdout);  
//
//
//    return 0;
//
//  }
