#ifndef  _DCS_kernel_VCaenHVBoard_h_
#define  _DCS_kernel_VCaenHVBoard_h_ 1

#include "VDeviceDriver.h"
#include "VValue.h"
#include "fwk/utlMessageBus.h"

#include<vector>

#include<cstdint>
#include<mutex>


//class CaenHVChannel{
//  public:
//    virtual ~CaenHVChannel(){}
//  protected:
//    CaenHVValue<float> fIMon,fVMon,fV0Set,fV1Set;
//    CaenHVValue<std::string> fName;
//};


class VCaenHVBoard:public VDeviceBase{
  public:
    VCaenHVBoard(const std::string& s, VDeviceBase*d);
  void Finalize(){}


    /**Parses the commands and calls the needed A7030
     * functions. The functions should internaly convert the
     * string to arguments or throw exception in case of
     * problem.
     */
    void SetParams(std::set<std::string>);
    virtual ~VCaenHVBoard(){}
    void SetNumChannels(unsigned int i){fNumberOfChannels=i;}
    void SetSlot       (unsigned int i){fSlotNumber      =i;}
    //void UpdateAll();  //TODO
    void AssertInit(){
      AssertNumberOfChannels();
      AssertBoardType();
    }
    private:
    const int &fCaenCrateHandle;
    std::mutex&fCaenCrateHandle_mutex;
  protected:
    virtual void AssertNumberOfChannels()=0;
    virtual void AssertBoardType()=0;

  private:
    void SetLocalParams(std::set<std::string>);
    void UpdateAllLocal(const std::string&str);

  protected:
    std::vector<int>         NumICommaDashListToVector  (std::string str);
    std::vector<float>       NumFCommaDashListToVector  (std::string str);
    std::vector<std::string> StringCommaDashListToVector(std::string str);


  protected:
    int fSlotNumber;
    int fNumberOfChannels;

    void GetCaenChParam(const std::string&par, void* res);
    //void SetCaenChParam(const std::string&par, void* res);
    void SetCaenChParam(const std::string& parname,std::vector<uint32_t> chans, std::vector<uint32_t   >vals);
    void SetCaenChParam(const std::string& parname,std::vector<uint32_t> chans, std::vector<float      >vals);
    void SetCaenChParam(const std::string& parname,std::vector<uint32_t> chans, std::vector<std::string>vals);

  public:// FIXME debug only
    void GetParentInfo(){INFO(GetParent()->GetName());}
    void DebugDump();

  protected: // CAEN Set functions. These to be called from the setting parser (separete thread)
    virtual void SetCaenChParam_Name   (const std::vector<uint32_t>&chlist,const std::vector<std::string>&vals)=0;
    virtual void SetCaenChParam_V0Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_I0Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_V1Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_I1Set  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_RUp    (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_RDWn   (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_Trip   (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_SVMax  (const std::vector<uint32_t>&chlist,const std::vector<float      >&vals)=0;
    virtual void SetCaenChParam_Pw     (const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals)=0;
    virtual void SetCaenChParam_TripInt(const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals)=0;
    virtual void SetCaenChParam_TripExt(const std::vector<uint32_t>&chlist,const std::vector<uint32_t   >&vals)=0;

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
    std::vector<CaenHVBoardValue<std::string>>fValuesName   ;
    std::vector<CaenHVBoardValue<float      >>fValuesV0Set  ;
    std::vector<CaenHVBoardValue<float      >>fValuesI0Set  ;
    std::vector<CaenHVBoardValue<float      >>fValuesV1Set  ;
    std::vector<CaenHVBoardValue<float      >>fValuesI1Set  ;
    std::vector<CaenHVBoardValue<float      >>fValuesRUp    ;
    std::vector<CaenHVBoardValue<float      >>fValuesRDWn   ;
    std::vector<CaenHVBoardValue<float      >>fValuesTrip   ;
    std::vector<CaenHVBoardValue<float      >>fValuesSVMax  ;
    std::vector<CaenHVBoardValue<float      >>fValuesVMon   ;
    std::vector<CaenHVBoardValue<float      >>fValuesIMon   ;
    std::vector<CaenHVBoardValue<uint32_t   >>fValuesStatus ;
    std::vector<CaenHVBoardValue<uint32_t   >>fValuesPw     ;
    std::vector<CaenHVBoardValue<uint32_t   >>fValuesTripInt;
    std::vector<CaenHVBoardValue<uint32_t   >>fValuesTripExt;
    //CaenHVBoardValue<ushort>     POn    ;
    //CaenHVBoardValue<ushort>     PDwn   ;

};

#endif
