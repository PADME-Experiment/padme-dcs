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
    T GetValue()const{
      return fValue;
    }
    double GetValueAge()const{
      time_t now;
      std::time(&now);
      return std::difftime(now,fLastUpdate);
    }


  protected:
    time_t fLastUpdate;
    T fValue;


};

#endif
