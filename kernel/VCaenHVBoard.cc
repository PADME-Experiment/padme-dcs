#include "VCaenHVBoard.h"   //in c file
#include"DrvCaenHV.h"
#include"fwk/utlCommaDashListToVector.h"
#include <caenlib/CAENHVWrapper.h>
#include<vector>
#include<bitset>
#include<sstream>



VCaenHVBoard::VCaenHVBoard(const std::string& s, VDeviceBase*d):
  VDeviceBase(s,d),
  fSlotNumber(-1),
  fCaenCrateHandle      (static_cast<DrvCaenHV*>(d)->GetCaenCrateHandle()),
  fCaenCrateHandle_mutex(static_cast<DrvCaenHV*>(d)->GetCaenCrateHandle_mutex()),
  fNumberOfChannels(-1)
{}


  void
VCaenHVBoard::GetCaenChParam(const std::string&par, void* res)
{
  std::vector<ushort> allch;
  allch.resize(fNumberOfChannels);
  for(int i=0;i<fNumberOfChannels;++i)allch[i]=i;
  int ret;
  std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
  ret=CAENHV_GetChParam(fCaenCrateHandle,fSlotNumber,
      par.c_str(), unsigned(fNumberOfChannels), &(*allch.begin()), res);
  if(ret!=CAENHV_OK) DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret,"try to get "+par);
}

  void
VCaenHVBoard::SetCaenChParam(const std::string& parname,std::vector<uint32_t> chans, std::vector<std::string>vals)
{
  const unsigned nch=chans.size();
  if(nch>fNumberOfChannels)throw fwk::Exception_tobefixed("SetCaenChParam vector too big");
  if(nch!=vals.size())throw fwk::Exception_tobefixed("SetCaenChParam vecotrs of different size");
  std::string allnames;
  for(auto it=vals.begin();it!=vals.end();++it)allnames.append(it->c_str(),it->size()+1); // +1 to add also '\0's
  std::vector<ushort> arr(nch);
  for(int i=0;i<nch;++i)arr[i]=chans[i];
  int ret;
  std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
  ret=CAENHV_SetChParam(fCaenCrateHandle,fSlotNumber, parname.c_str(), nch, &(*arr.begin()), (char*)allnames.c_str());
  if(ret!=CAENHV_OK) DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret,"try to set "+parname);
}

  void
VCaenHVBoard::SetCaenChParam(const std::string& parname,std::vector<uint32_t> chans, std::vector<float>vals)
{
  const unsigned nch=chans.size();
  if(nch>fNumberOfChannels)throw fwk::Exception_tobefixed("SetCaenChParam vector too big");
  if(nch!=vals.size())throw fwk::Exception_tobefixed("SetCaenChParam vecotrs of different size");
  std::vector<ushort> arr(nch);
  for(int i=0;i<nch;++i)arr[i]=chans[i];
  for(int i=0;i<nch;++i)INFO(std::to_string(chans[i])+"   "+std::to_string(vals[i]));
  INFO(parname);
  int ret;
  std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
  ret=CAENHV_SetChParam(fCaenCrateHandle,fSlotNumber, parname.c_str(), nch, &(*arr.begin()), &(vals[0]));
  if(ret!=CAENHV_OK) DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret,"try to set "+parname);
}

  void
VCaenHVBoard::SetCaenChParam(const std::string& parname,std::vector<uint32_t> chans, std::vector<uint32_t>vals)
{
  const unsigned nch=chans.size();
  if(nch>fNumberOfChannels)throw fwk::Exception_tobefixed("SetCaenChParam vector too big");
  if(nch!=vals.size())throw fwk::Exception_tobefixed("SetCaenChParam vecotrs of different size");
  std::vector<ushort> arr(nch);
  for(int i=0;i<nch;++i)arr[i]=chans[i];
  int ret;
  std::lock_guard<std::mutex> guard(fCaenCrateHandle_mutex);
  ret=CAENHV_SetChParam(fCaenCrateHandle,fSlotNumber, parname.c_str(), nch, &(*arr.begin()), &(vals[0]));
  if(ret!=CAENHV_OK) DrvCaenHV_except::CAENWrapperRetStatus(fCaenCrateHandle,ret,"try to set "+parname);
}



  void
VCaenHVBoard::SetParams(std::set<std::string>setstr)
{
  //TODO
  //parses the commands and calls the needed A7030 functions
  // the functions should internaly convert the string
  // to arguments or throw exception in case of problem
  // IFs ELSEs
  // converts strings to vectors
  for(auto set_it=setstr.begin();set_it!=setstr.end();++set_it){
    INFO(*set_it);
    std::stringstream liness(*set_it);
    std::string cmd,chans,vals;
    std::vector<std::string> vvalS;
    std::vector<unsigned int> vvalI;
    std::vector<float> vvalF;

    if(liness>>cmd>>chans>>vals)INFO("THROW");//throw fwk::Exception_tobefixed("VCaenHVBoard::SetParams line syntax error");
    INFO("cmd  "+cmd  );
    INFO("chans"+chans);
    INFO("vals "+vals );
    if( cmd.size()==0     ||
        chans.size()==0 ||
        vals.size()==0  ){
      INFO("THROW");}//throw fwk::Exception_tobefixed("VCaenHVBoard::SetParams line syntax error");

    std::vector<unsigned int>vchans=utl::NumICommaDashListToVector(chans);
    if(!(vchans.size()>0))INFO("THROW");//throw fwk::Exception_tobefixed("VCaenHVBoard::SetParams syntax error vchans=0");

    if(cmd=="Name"){
      vvalS=utl::StringCommaDashListToVector(vals);
      if(vvalS.size()==1){
        vvalS.resize(vchans.size(),vvalS[0]);
      }
      if(vvalS.size()!=vchans.size())INFO("THROW");//throw fwk::Exception_tobefixed("VCaenHVBoard::SetParams syntax error vchans.size!=vvalS.size");

    }else if(
        cmd=="V0Set"||
        cmd=="I0Set"||
        cmd=="V1Set"||
        cmd=="I1Set"||
        cmd=="RUp"  ||
        cmd=="RDWn" ||
        cmd=="Trip" ||
        cmd=="SVMax"){
      vvalF=utl::NumFCommaDashListToVector(vals);
      if(vvalF.size()==1){
        vvalF.resize(vchans.size(),vvalF[0]);
        INFO("setting float");
      }
      INFO("vchans.size"+std::to_string(vchans.size()));
      INFO("vvalF.size"+std::to_string(vvalF.size()));
      if(vvalF.size()!=vchans.size())throw fwk::Exception_tobefixed("VCaenHVBoard::SetParams syntax error vchans.size!=vvalF.size");
    } else if( cmd=="Pw"||
        cmd=="TripInt"  ||
        cmd=="TripExt"){
      vvalI=utl::NumICommaDashListToVector(vals);
      if(vvalI.size()==1){
        vvalI.resize(vchans.size(),vvalI[0]);
      }
      if(vvalI.size()!=vchans.size())throw fwk::Exception_tobefixed("VCaenHVBoard::SetParams syntax error vchans.size!=vvalI.size");
    }else throw fwk::Exception_tobefixed("VCaenHVBoard::SetParams syntax error");

    if(cmd=="Name"   )SetCaenChParam_Name   (vchans,vvalS);
    if(cmd=="V0Set"  )SetCaenChParam_V0Set  (vchans,vvalF);
    if(cmd=="I0Set"  )SetCaenChParam_I0Set  (vchans,vvalF);
    if(cmd=="V1Set"  )SetCaenChParam_V1Set  (vchans,vvalF);
    if(cmd=="I1Set"  )SetCaenChParam_I1Set  (vchans,vvalF);
    if(cmd=="RUp"    )SetCaenChParam_RUp    (vchans,vvalF);
    if(cmd=="RDWn"   )SetCaenChParam_RDWn   (vchans,vvalF);
    if(cmd=="Trip"   )SetCaenChParam_Trip   (vchans,vvalF);
    if(cmd=="SVMax"  )SetCaenChParam_SVMax  (vchans,vvalF);
    if(cmd=="Pw"     )SetCaenChParam_Pw     (vchans,vvalI);
    if(cmd=="TripInt")SetCaenChParam_TripInt(vchans,vvalI);
    if(cmd=="TripExt")SetCaenChParam_TripExt(vchans,vvalI);
  }
}
















//        FIXME    DEBUG STARTS HERE


  void
VCaenHVBoard::DebugDump()
{
  std::stringstream ss;
  //ss.str(std::string());ss.clear(); ss<<"Name   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesName [i].GetVal()<<"("<<fValuesName [i].GetAge()<<"s)"; } INFO(ss.str());

  ss.str(std::string());ss.clear(); ss<<"V0Set  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesV0Set[i].GetVal()<<"("<<fValuesV0Set[i].GetAge()<<"s)"; } INFO(ss.str());

  //  ss.str(std::string());ss.clear(); ss<<"I0Set  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesI0Set[i].GetVal()<<"("<<fValuesI0Set[i].GetAge()<<"s)"; } INFO(ss.str());
  //  ss.str(std::string());ss.clear(); ss<<"V1Set  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesV1Set[i].GetVal()<<"("<<fValuesV1Set[i].GetAge()<<"s)"; } INFO(ss.str());
  //  ss.str(std::string());ss.clear(); ss<<"I1Set  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesI1Set[i].GetVal()<<"("<<fValuesI1Set[i].GetAge()<<"s)"; } INFO(ss.str());
  //  ss.str(std::string());ss.clear(); ss<<"RUp    "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesRUp  [i].GetVal()<<"("<<fValuesRUp  [i].GetAge()<<"s)"; } INFO(ss.str());
  //  ss.str(std::string());ss.clear(); ss<<"RDWn   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesRDWn [i].GetVal()<<"("<<fValuesRDWn [i].GetAge()<<"s)"; } INFO(ss.str());
  //  ss.str(std::string());ss.clear(); ss<<"Trip   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesTrip [i].GetVal()<<"("<<fValuesTrip [i].GetAge()<<"s)"; } INFO(ss.str());
  //  ss.str(std::string());ss.clear(); ss<<"SVMax  "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesSVMax[i].GetVal()<<"("<<fValuesSVMax[i].GetAge()<<"s)"; } INFO(ss.str());
  //ss.str(std::string());ss.clear(); ss<<"VMon   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesVMon [i].GetVal()<<"("<<fValuesVMon [i].GetAge()<<"s)"; } INFO(ss.str());
  //ss.str(std::string());ss.clear(); ss<<"IMon   "; for(int i=0;i<fNumberOfChannels;++i){ ss<<fValuesIMon [i].GetVal()<<"("<<fValuesIMon [i].GetAge()<<"s)"; } INFO(ss.str());

  ss.str(std::string());ss.clear(); ss<<"Status    "; for(int i=0;i<fNumberOfChannels;++i){ ss<<" 0x"<<std::bitset<16>(fValuesStatus [i].GetVal())<<"("<<fValuesStatus [i].GetAge()<<"s)"; } INFO(ss.str());
  //ss.str(std::string());ss.clear(); ss<<"Pw        "; for(int i=0;i<fNumberOfChannels;++i){ ss<<" 0x"<<std::bitset< 3>(fValuesPw     [i].GetVal())<<"("<<fValuesPw     [i].GetAge()<<"s)"; } INFO(ss.str());
  //  ss.str(std::string());ss.clear(); ss<<"TripIntPw "; for(int i=0;i<fNumberOfChannels;++i){ ss<<" 0x"<<std::bitset< 3>(fValuesTripInt[i].GetVal())<<"("<<fValuesTripInt[i].GetAge()<<"s)"; } INFO(ss.str());
  //  ss.str(std::string());ss.clear(); ss<<"TripExtPw "; for(int i=0;i<fNumberOfChannels;++i){ ss<<" 0x"<<std::bitset< 3>(fValuesTripExt[i].GetVal())<<"("<<fValuesTripExt[i].GetAge()<<"s)"; } INFO(ss.str());
}

