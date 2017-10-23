#include "DrvCaenA7030.h"   //in c file
#include "VCaenHVBoard.h"   //in c file
#include"fwk/utlMessageBus.h"
#include<string>

//#include <caenlib/CAENHVWrapper.h>




  void
DrvCaenA7030N::AssertNumberOfChannels()
{
  INFO(std::to_string(fNumberOfChannels));

  //TODO
  //should throw special type
  //when thrown board should be deleted
}

  void
DrvCaenA7030N::AssertBoardType()
{
  //TODO
  //should throw special type
  //when thrown board should be deleted
  INFO(std::to_string(fNumberOfChannels));
  if(fNumberOfChannels<1)throw fwk::Exception_tobefixed("fNumberoFChannels<1");
  if(fNumberOfChannels!=48)throw fwk::Exception_tobefixed("fNumberoFChannels!=48");
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



void DrvCaenA7030N::GetCaenChParam_Name   (){char res[640];GetCaenChParam("Name"   ,res);/*TODO da se polzva onazi fukciya za splitvaneto*/}
void DrvCaenA7030N::GetCaenChParam_V0Set  (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("V0Set"  ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesV0Set  [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_I0Set  (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("I0Set"  ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesI0Set  [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_V1Set  (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("V1Set"  ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesV1Set  [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_I1Set  (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("I1Set"  ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesI1Set  [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_RUp    (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("RUp"    ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesRUp    [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_RDWn   (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("RDWn"   ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesRDWn   [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_Trip   (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("Trip"   ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesTrip   [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_SVMax  (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("SVMax"  ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesSVMax  [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_VMon   (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("VMon"   ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesVMon   [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_IMon   (){std::vector<float   >res(fNumberOfChannels);GetCaenChParam("IMon"   ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesIMon   [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_Status (){std::vector<uint32_t>res(fNumberOfChannels);GetCaenChParam("Status" ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesStatus [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_Pw     (){std::vector<uint32_t>res(fNumberOfChannels);GetCaenChParam("Pw"     ,&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesPw     [i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_TripInt(){std::vector<uint32_t>res(fNumberOfChannels);GetCaenChParam("TripInt",&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesTripInt[i].SetVal(res[i]);}}
void DrvCaenA7030N::GetCaenChParam_TripExt(){std::vector<uint32_t>res(fNumberOfChannels);GetCaenChParam("TripExt",&(*res.begin()));for(int i=0;i<fNumberOfChannels;++i){fValuesTripExt[i].SetVal(res[i]);}}



void DrvCaenA7030N::SetCaenChParam_Name   (const std::vector<uint32_t>&chlist,const std::vector<std::string>&vals){SetCaenChParam("Name"   ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_V0Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals){SetCaenChParam("V0Set"  ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_I0Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals){SetCaenChParam("I0Set"  ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_V1Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals){SetCaenChParam("V1Set"  ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_I1Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals){SetCaenChParam("I1Set"  ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_RUp    (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals){SetCaenChParam("RUp"    ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_RDWn   (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals){SetCaenChParam("RDWn"   ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_Trip   (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals){SetCaenChParam("Trip"   ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_SVMax  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals){SetCaenChParam("SVMax"  ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_Pw     (const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals){SetCaenChParam("Pw"     ,chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_TripInt(const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals){SetCaenChParam("TripInt",chlist,vals);}
void DrvCaenA7030N::SetCaenChParam_TripExt(const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals){SetCaenChParam("TripExt",chlist,vals);}
