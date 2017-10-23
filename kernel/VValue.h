#ifndef  _DCS_kernel_VValue_h_
#define  _DCS_kernel_VValue_h_ 1
#include "VValue.h"   //in c file
#include<ctime>
#include<mutex>


template <class T>
class VValue{
  public:
    VValue():
      fLastUpdate(0) {}
    virtual ~VValue(){}
    /// Because of mutex.
    VValue(const VValue&){}
    void SetVal(const T & val){
      std::lock_guard<std::mutex> guard(fValue_mutex);
      this->fValue=val;
      std::time(&fLastUpdate);
    }
    T GetVal(){
      std::lock_guard<std::mutex> guard(fValue_mutex);
      return fValue;
    }
    double GetAge(){
      std::lock_guard<std::mutex> guard(fValue_mutex);
      return std::difftime(std::time(nullptr),fLastUpdate);
    }


  protected:
    time_t fLastUpdate;
    T fValue;
    std::mutex fValue_mutex;///< mutex barrier for value
};


template <class T>
class CaenHVCrateValue:public VValue<T>{
  public:
  CaenHVCrateValue():VValue<T>(){}
  ~CaenHVCrateValue(){}

};

template<class T>
class CaenHVBoardValue:public VValue<T>{
  public:
  CaenHVBoardValue():VValue<T>(){}
  ~CaenHVBoardValue(){}
};


#endif
