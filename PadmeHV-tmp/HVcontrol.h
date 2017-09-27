#ifndef __HVcontrol_h__
#define __HVcontrol_h__ 0
#include<vector>


int SetVoltage(int handle,unsigned int voltageToBeSet);
int SetPower(int handle,int pw);
int GetVMon(int handle);
int GetIMon(int handle);
int GetZ(int handle);
int GetStatus(int handle);
int Connect(int& handle);
int Disconnect(int handle);

std::vector<short unsigned int> gListOfChannels;


//int check_HV(unsigned short nr_of_ch, int Hndl, unsigned short* listach, char (*chname)[MAX_CH_NAME], int* slot_ch, int* Statuslist, float* Vlist, float* Ilist, int print);

#endif
