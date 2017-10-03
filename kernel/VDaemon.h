#ifndef  _DCS_kernel_VDaemon_h_
#define  _DCS_kernel_VDaemon_h_ 1
#include <thread>

class VDaemonSingleThread{
  public:
    VDaemonSingleThread():fRun(false){}
    virtual ~VDaemonSingleThread(){}

    void Daemonize();
    void Kill();
  protected:
    bool fRun;
    void StartCycling();
    virtual void OnStart()=0;
    virtual void OnCycle()=0;
    virtual void OnStop()=0;
    //std::thread* fThread;
};


#endif
