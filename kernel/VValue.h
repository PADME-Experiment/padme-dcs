#ifndef  _DCS_kernel_VValue_h_
#define  _DCS_kernel_VValue_h_ 1
#include "VValue.h"   //in c file
#include<ctime>


template <class T>
class VValue{
  public:
    VValue():
      fLastUpdate(0) {}
    virtual ~VValue(){}
    const T& operator<<(const T & rhs){
      this->fValue=rhs;
      std::time(&fLastUpdate);
      return fValue;
    }
    T GetVal()const{ return fValue; }
    double GetAge()const{
      time_t now;
      std::time(&now);
      return std::difftime(now,fLastUpdate);
    }


  protected:
    time_t fLastUpdate;
    T fValue;
};


template <class T>
class CaenHVCrateValue:public VValue<T>{
};


#endif
