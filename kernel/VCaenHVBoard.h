#ifndef  _DCS_kernel_VCaenHVBoard_h_
#define  _DCS_kernel_VCaenHVBoard_h_ 1

#include "VDeviceDriver.h"
#include "VValue.h"

#include<vector>

#include<cstdint>

template<class T>
class CaenHVValue:public VValue<T>{
  public:
};

//class CaenHVChannel{
//  public:
//    virtual ~CaenHVChannel(){}
//  protected:
//    CaenHVValue<float> fIMon,fVMon,fV0Set,fV1Set;
//    CaenHVValue<std::string> fName;
//};


class VCaenHVBoard:public VDeviceDriver{
  public:
    VCaenHVBoard(const std::string& s, std::shared_ptr<VDeviceDriver>d):
      VDeviceDriver(s,d),
      fSlotNumber(-1),
      fNumberOfChannels(-1)
  {}


    /**Parses the commands and calls the needed A7030
     * functions. The functions should internaly convert the
     * string to arguments or throw exception in case of
     * problem.
     */
    void SetParams(int caenHandle,std::set<std::string>);
    virtual ~VCaenHVBoard(){}
    void SetNumChannels(unsigned int i){fNumberOfChannels=i;}
    void SetSlot       (unsigned int i){fSlotNumber      =i;}
    //void UpdateAll();  //TODO
    void AssertInit(){
      AssertNumberOfChannels();
      AssertBoardType();
    }
  protected:
    virtual void AssertNumberOfChannels()=0;
    virtual void AssertBoardType()=0;


  protected:
    std::vector<int>         NumICommaDashListToVector  (std::string str);
    std::vector<float>       NumFCommaDashListToVector  (std::string str);
    std::vector<std::string> StringCommaDashListToVector(std::string str);


  protected:
    int fSlotNumber;
    int fNumberOfChannels;

    void GetCaenChParam(const std::string&par, void* res);
    //void SetCaenChParam(const std::string&par, void* res);
    void SetCaenChParam(int handle,const std::string& parname,std::vector<uint32_t> chans, std::vector<uint32_t   >vals);
    void SetCaenChParam(int handle,const std::string& parname,std::vector<uint32_t> chans, std::vector<float      >vals);
    void SetCaenChParam(int handle,const std::string& parname,std::vector<uint32_t> chans, std::vector<std::string>vals);

  public:// FIXME debug only
    void GetParentInfo(){INFO(GetParent()->GetName());}
    void GetUpdateAll(){
      //GetChParam_Name   ();
      GetCaenChParam_V0Set  ();
      GetCaenChParam_I0Set  ();
      GetCaenChParam_V1Set  ();
      GetCaenChParam_I1Set  ();
      GetCaenChParam_RUp    ();
      GetCaenChParam_RDWn   ();
      GetCaenChParam_Trip   ();
      GetCaenChParam_SVMax  ();
      GetCaenChParam_VMon   ();
      GetCaenChParam_IMon   ();
      GetCaenChParam_Status ();
      GetCaenChParam_Pw     ();
      GetCaenChParam_TripInt();
      GetCaenChParam_TripExt();
    }
    void DebugDump();

  protected: // CAEN Set functions. These to be called from the setting parser (separete thread)
    virtual void SetCaenChParam_Name   (int handle,const std::vector<uint32_t>&chlist,const std::vector<std::string>&vals)=0;
    virtual void SetCaenChParam_V0Set  (int handle,const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_I0Set  (int handle,const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_V1Set  (int handle,const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_I1Set  (int handle,const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_RUp    (int handle,const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_RDWn   (int handle,const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_Trip   (int handle,const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_SVMax  (int handle,const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_Pw     (int handle,const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals)=0;
    virtual void SetCaenChParam_TripInt(int handle,const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals)=0;
    virtual void SetCaenChParam_TripExt(int handle,const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals)=0;

  protected: // CAEN Get functions. These to be called from update function
    virtual void GetCaenChParam_Name   ()=0;
    virtual void GetCaenChParam_V0Set  ()=0;
    virtual void GetCaenChParam_I0Set  ()=0;
    virtual void GetCaenChParam_V1Set  ()=0;
    virtual void GetCaenChParam_I1Set  ()=0;
    virtual void GetCaenChParam_RUp    ()=0;
    virtual void GetCaenChParam_RDWn   ()=0;
    virtual void GetCaenChParam_Trip   ()=0;
    virtual void GetCaenChParam_SVMax  ()=0;
    virtual void GetCaenChParam_VMon   ()=0;
    virtual void GetCaenChParam_IMon   ()=0;
    virtual void GetCaenChParam_Status ()=0;
    virtual void GetCaenChParam_Pw     ()=0;
    virtual void GetCaenChParam_TripInt()=0;
    virtual void GetCaenChParam_TripExt()=0;

  protected: // CAEN board variables
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
    std::vector<CaenHVValue<uint32_t   >>fValuesStatus ;
    std::vector<CaenHVValue<uint32_t   >>fValuesPw     ;
    std::vector<CaenHVValue<uint32_t   >>fValuesTripInt;
    std::vector<CaenHVValue<uint32_t   >>fValuesTripExt;
    //CaenHVValue<ushort>     POn    ;
    //CaenHVValue<ushort>     PDwn   ;

};

#endif
