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
    DrvCaenA7030N(const std::string& s, std::shared_ptr<VDeviceDriver>d):VCaenHVBoard(s,d){INFO("");}
    ~DrvCaenA7030N(){INFO("");}
    void SetNumberOfChannels(int i){fNumberOfChannels=i;}
    void SetSlotNumber(int i){fSlotNumber=i;}
    void AssertInit(){ /// Make sure that the type of the board(TODO) is as expected allocate mem
    if(fNumberOfChannels<1)throw fwk::Exception_tobefixed("fNumberoFChannels<1");
      fValuesName   .resize(fNumberOfChannels);
      fValuesV0Set  .resize(fNumberOfChannels);
      fValuesI0Set  .resize(fNumberOfChannels);
      fValuesV1Set  .resize(fNumberOfChannels);
      fValuesI1Set  .resize(fNumberOfChannels);
      fValuesRUp    .resize(fNumberOfChannels);
      fValuesRDWn   .resize(fNumberOfChannels);
      fValuesTrip   .resize(fNumberOfChannels);
      fValuesSVMax  .resize(fNumberOfChannels);
      fValuesVMon   .resize(fNumberOfChannels);
      fValuesIMon   .resize(fNumberOfChannels);
      fValuesStatus .resize(fNumberOfChannels);
      fValuesPw     .resize(fNumberOfChannels);
      fValuesTripInt.resize(fNumberOfChannels);
      fValuesTripExt.resize(fNumberOfChannels);
    }


  public:// FIXME debug only
    void GetParentInfo(){INFO(GetParent()->GetName());}
    void DebugUpdate(){
      //GetChParam_Name   ();
      GetChParam_V0Set  ();
      GetChParam_I0Set  ();
      GetChParam_V1Set  ();
      GetChParam_I1Set  ();
      GetChParam_RUp    ();
      GetChParam_RDWn   ();
      GetChParam_Trip   ();
      GetChParam_SVMax  ();
      GetChParam_VMon   ();
      GetChParam_IMon   ();
      GetChParam_Status ();
      GetChParam_Pw     ();
      GetChParam_TripInt();
      GetChParam_TripExt();
    }
    void DebugDump(){
      std::stringstream ss;
      ss.str(std::string());ss.clear(); ss<<"Name   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesName [i].GetVal()<<"("<<fValuesName [i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"V0Set  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesV0Set[i].GetVal()<<"("<<fValuesV0Set[i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"I0Set  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesI0Set[i].GetVal()<<"("<<fValuesI0Set[i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"V1Set  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesV1Set[i].GetVal()<<"("<<fValuesV1Set[i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"I1Set  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesI1Set[i].GetVal()<<"("<<fValuesI1Set[i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"RUp    "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesRUp  [i].GetVal()<<"("<<fValuesRUp  [i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"RDWn   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesRDWn [i].GetVal()<<"("<<fValuesRDWn [i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"Trip   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesTrip [i].GetVal()<<"("<<fValuesTrip [i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"SVMax  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesSVMax[i].GetVal()<<"("<<fValuesSVMax[i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"VMon   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesVMon [i].GetVal()<<"("<<fValuesVMon [i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"IMon   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesIMon [i].GetVal()<<"("<<fValuesIMon [i].GetAge()<<"s)"; } INFO(ss.str());

      ss.str(std::string());ss.clear(); ss<<"Status    "; for(int i=0;i<fNumberOfChannels;++i){ ss<<" 0x"<<std::bitset<16>(fValuesStatus [i].GetVal())<<"("<<fValuesStatus [i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"Pw        "; for(int i=0;i<fNumberOfChannels;++i){ ss<<" 0x"<<std::bitset< 3>(fValuesPw     [i].GetVal())<<"("<<fValuesPw     [i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"TripIntPw "; for(int i=0;i<fNumberOfChannels;++i){ ss<<" 0x"<<std::bitset< 3>(fValuesTripInt[i].GetVal())<<"("<<fValuesTripInt[i].GetAge()<<"s)"; } INFO(ss.str());
      ss.str(std::string());ss.clear(); ss<<"TripExtPw "; for(int i=0;i<fNumberOfChannels;++i){ ss<<" 0x"<<std::bitset< 3>(fValuesTripExt[i].GetVal())<<"("<<fValuesTripExt[i].GetAge()<<"s)"; } INFO(ss.str());
    }
  private:
    std::vector<CaenHVValue<std::string>>fValuesName   ;
    std::vector<CaenHVValue<float      >>fValuesV0Set  ;
    std::vector<CaenHVValue<float      >>fValuesI0Set  ;
    std::vector<CaenHVValue<float      >>fValuesV1Set  ;
    std::vector<CaenHVValue<float      >>fValuesI1Set  ;
    std::vector<CaenHVValue<float      >>fValuesRUp    ;
    std::vector<CaenHVValue<float      >>fValuesRDWn   ;
    std::vector<CaenHVValue<float      >>fValuesTrip   ;
    std::vector<CaenHVValue<float      >>fValuesSVMax  ;
    std::vector<CaenHVValue<float      >>fValuesVMon   ;
    std::vector<CaenHVValue<float      >>fValuesIMon   ;
    std::vector<CaenHVValue<uint16_t   >>fValuesStatus ;
    std::vector<CaenHVValue<uint16_t   >>fValuesPw     ;
    std::vector<CaenHVValue<uint16_t   >>fValuesTripInt;
    std::vector<CaenHVValue<uint16_t   >>fValuesTripExt;
    //CaenHVValue<ushort>     POn    ;
    //CaenHVValue<ushort>     PDwn   ;
  private:// functions
    void GetChParam_Name   ();
    void GetChParam_V0Set  ();
    void GetChParam_I0Set  ();
    void GetChParam_V1Set  ();
    void GetChParam_I1Set  ();
    void GetChParam_RUp    ();
    void GetChParam_RDWn   ();
    void GetChParam_Trip   ();
    void GetChParam_SVMax  ();
    void GetChParam_VMon   ();
    void GetChParam_IMon   ();
    void GetChParam_Status ();
    void GetChParam_Pw     ();
    void GetChParam_TripInt();
    void GetChParam_TripExt();
};

#endif
