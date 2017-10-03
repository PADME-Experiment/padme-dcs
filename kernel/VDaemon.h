#ifndef  _DCS_kernel_VDaemon_h_
#define  _DCS_kernel_VDaemon_h_ 1
#include <thread>

class VDaemonSingleThread{
  public:
    VDaemonSingleThread():fRun(false){}
    virtual ~VDaemonSingleThread(){}

    void Daemonize();
    void KillThread();
    void StopThread();
    void JoinThread();
  protected:
    bool fRun;
    void StartCycling();
    virtual void OnStart() =0;
    virtual void OnCycle() =0;//std::this_thread::sleep_for(std::chrono::seconds(1));
    virtual void OnStop()  =0;
    std::thread* fThread;
};


#endif
