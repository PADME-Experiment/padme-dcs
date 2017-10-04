#ifndef  _DCS_kernel_VDaemon_h_
#define  _DCS_kernel_VDaemon_h_ 1
#include <thread>
#include <mutex>
#include<list>
#include "fwk/utlMessageBus.h"

class VDaemonSingleThread{
  public:
    VDaemonSingleThread():fRun(false){}
    virtual ~VDaemonSingleThread(){}

    void Daemonize();
    void KillThread();
    void StopThread();
    void JoinThread();
  protected:
    void StartCycling();
    virtual void OnStart() =0;
    virtual void OnCycle() =0;//std::this_thread::sleep_for(std::chrono::seconds(1));
    virtual void OnStop()  =0;

  protected:
    std::thread* fThread;
    bool fRun;
};

class VDaemonService{
  public:
    virtual ~VDaemonService(){}
    void KillAll(); // TODO REMOVE
    void Daemonize();
  protected:
    virtual void Service()=0;

    protected:
    //std::list<std::unique_ptr<std::thread>> fThreads;
    //std::mutex fDaemonizeBarrier;
};

class VDaemonServiceTCP:public VDaemonService{
  public:
    VDaemonServiceTCP(int port):fPort(port){Initialize();}
    virtual ~VDaemonServiceTCP(){INFO("");Finalize();}

  protected:
    virtual void ServiceLoop(const int fd);//=0{} FIXME should be pure virtual
    void Service();
    void Initialize();
    void Finalize();

  protected:
    int fPort;
    int fServiceSocket;

};


#endif
