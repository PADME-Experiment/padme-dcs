#ifndef  _DCS_kernel_DrvCaenA7030_h_
#define  _DCS_kernel_DrvCaenA7030_h_ 1
#include "DrvCaenA7030.h"   //in c file
#include "VCaenHVBoard.h"

#include "fwk/utlMessageBus.h"
#include "fwk/fwkException.h"

#include <string>
#include<cstdint>
#include<vector>
#include <bitset>         // std::bitset

class DrvCaenA7030N:public VCaenHVBoard{
  public:
    DrvCaenA7030N(const std::string& s, VDeviceBase*d):VCaenHVBoard(s,d){INFO("");}
    ~DrvCaenA7030N(){INFO("");}
    void SetNumberOfChannels(int i){fNumberOfChannels=i;}
    void SetSlotNumber(int i){fSlotNumber=i;}
    /// Make sure that the type of the board(TODO) is as expected allocate mem
    void AssertNumberOfChannels();
    void AssertBoardType();
  protected: // CAEN Set functions. These to be called from the setting parser (separete thread)
    void SetCaenChParam_Name   (const std::vector<uint32_t>&chlist,const std::vector<std::string>&vals);
    void SetCaenChParam_V0Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals);
    void SetCaenChParam_I0Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals);
    void SetCaenChParam_V1Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals);
    void SetCaenChParam_I1Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals);
    void SetCaenChParam_RUp    (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals);
    void SetCaenChParam_RDWn   (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals);
    void SetCaenChParam_Trip   (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals);
    void SetCaenChParam_SVMax  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals);
    void SetCaenChParam_Pw     (const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals);
    void SetCaenChParam_TripInt(const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals);
    void SetCaenChParam_TripExt(const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals);

  protected: // CAEN Get functions. These to be called from update function
    void GetCaenChParam_Name   ();
    void GetCaenChParam_V0Set  ();
    void GetCaenChParam_I0Set  ();
    void GetCaenChParam_V1Set  ();
    void GetCaenChParam_I1Set  ();
    void GetCaenChParam_RUp    ();
    void GetCaenChParam_RDWn   ();
    void GetCaenChParam_Trip   ();
    void GetCaenChParam_SVMax  ();
    void GetCaenChParam_VMon   ();
    void GetCaenChParam_IMon   ();
    void GetCaenChParam_Status ();
    void GetCaenChParam_Pw     ();
    void GetCaenChParam_TripInt();
    void GetCaenChParam_TripExt();
};



#endif
