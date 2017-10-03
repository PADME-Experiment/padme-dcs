#include "DrvCaenA7030.h"   //in c file
#include "VCaenHVBoard.h"   //in c file
#include"fwk/utlMessageBus.h"
#include<string>

#include <caenlib/CAENHVWrapper.h>

    //void GetChParam(const std::string&par, void* res);

    void DrvCaenA7030N::GetChParam_Name   (){char res[640];GetChParam("Name"   ,res);/*TODO da se polzva onazi fukciya za splitvaneto*/}
    void DrvCaenA7030N::GetChParam_V0Set  (){float    res[fNumberOfChannels];GetChParam("V0Set"  ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesV0Set  [i]<<res[i];INFO(std::to_string(res[i]));}}
    void DrvCaenA7030N::GetChParam_I0Set  (){float    res[fNumberOfChannels];GetChParam("I0Set"  ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesI0Set  [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_V1Set  (){float    res[fNumberOfChannels];GetChParam("V1Set"  ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesV1Set  [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_I1Set  (){float    res[fNumberOfChannels];GetChParam("I1Set"  ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesI1Set  [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_RUp    (){float    res[fNumberOfChannels];GetChParam("RUp"    ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesRUp    [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_RDWn   (){float    res[fNumberOfChannels];GetChParam("RDWn"   ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesRDWn   [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_Trip   (){float    res[fNumberOfChannels];GetChParam("Trip"   ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesTrip   [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_SVMax  (){float    res[fNumberOfChannels];GetChParam("SVMax"  ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesSVMax  [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_VMon   (){float    res[fNumberOfChannels];GetChParam("VMon"   ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesVMon   [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_IMon   (){float    res[fNumberOfChannels];GetChParam("IMon"   ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesIMon   [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_Status (){uint16_t res[fNumberOfChannels];GetChParam("Status" ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesStatus [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_Pw     (){uint16_t res[fNumberOfChannels];GetChParam("Pw"     ,res);for(int i=0;i<fNumberOfChannels;++i){fValuesPw     [i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_TripInt(){uint16_t res[fNumberOfChannels];GetChParam("TripInt",res);for(int i=0;i<fNumberOfChannels;++i){fValuesTripInt[i]<<res[i];}}
    void DrvCaenA7030N::GetChParam_TripExt(){uint16_t res[fNumberOfChannels];GetChParam("TripExt",res);for(int i=0;i<fNumberOfChannels;++i){fValuesTripExt[i]<<res[i];}}
