#ifndef  _DCS_kernel_VCaenHVBoard_h_
#define  _DCS_kernel_VCaenHVBoard_h_ 1

#include "VDeviceDriver.h"
#include "VValue.h"


template<class T>
class CaenHVValue:public VValue<T>{
  public:
};

class CaenHVChannel{
  public:
    virtual ~CaenHVChannel(){}
  protected:
    CaenHVValue<float> fIMon,fVMon,fV0Set,fV1Set;
    CaenHVValue<std::string> fName;
};

class VCaenHVBoard:public VDeviceDriver{
  public:
    VCaenHVBoard(const std::string& s, std::shared_ptr<VDeviceDriver>d):VDeviceDriver(s,d){}
    virtual ~VCaenHVBoard(){}
    void SetNumChannels(unsigned int i){fNumberOfChannels=i;}
    void SetSlot       (unsigned int i){fSlotNumber      =i;}
  protected:
    unsigned int fNumberOfChannels;
    unsigned int fSlotNumber;
    void AssertNumberOfChannels(){
#warning todo
      //should throw special type
      //when thrown board should be deleted
    }
    void AssertBoardType(){
#warning todo
      //should throw special type
      //when thrown board should be deleted
    }
    void Assert(){
      AssertNumberOfChannels();
      AssertBoardType();
    }

  protected:


};

#endif
