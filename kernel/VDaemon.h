#ifndef  _DCS_kernel_VDaemon_h_
#define  _DCS_kernel_VDaemon_h_ 1
#include "fwk/utlMessageBus.h"

#include<thread>
#include<mutex>
#include<list>
#include<string>


class VDaemonBase{
  public:
    VDaemonBase(){}
    virtual ~VDaemonBase(){}
    virtual void Daemonize ()=0;
    virtual void AssertInit()=0;
    virtual void Finalize  ()=0;
    virtual const std::string& GetName()const =0;
};

class VDaemonSingleThread:public VDaemonBase{
  public:
    void Daemonize ();
    virtual void AssertInit(){}
    virtual void Finalize  (){}
  public:
    VDaemonSingleThread():fRun(false),fThread(nullptr){}
    virtual ~VDaemonSingleThread(){}

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

class VDaemonService:public VDaemonBase{
  public:
    void Daemonize ();
    virtual void AssertInit(){}
    virtual void Finalize  (){}
  public:
    virtual ~VDaemonService(){}
    VDaemonService(const std::string&lab):fLabel(lab){}
    void KillAll(); // TODO REMOVE
    const std::string& GetName()const{return fLabel;}
  protected:
    virtual void Service()=0;
    std::string fLabel; ///< full path PADME/xxx/yyy/zzz

  protected:
    //std::list<std::unique_ptr<std::thread>> fThreads;
    //std::mutex fDaemonizeBarrier;
};

class VDaemonServiceTCP:public VDaemonService{
  public:
    VDaemonServiceTCP(const std::string&lab,int port):fPort(port),VDaemonService(lab){Initialize();}
    virtual ~VDaemonServiceTCP(){INFO("");Finalize();}

  protected:
    virtual void ServiceLoop(const int fd)=0;//{} FIXME should be pure virtual
    void Service();
    void Initialize();
    void Finalize();

  protected:
    int fPort;
    int fServiceSocket;

};

#include<string>
#include<set>
#include<mutex>
class ServiceTCPConfigure:public VDaemonServiceTCP{
  public:
    ServiceTCPConfigure(const std::string&lab,int portN):VDaemonServiceTCP(lab,portN){}
    void ServiceLoop(const int fd);
    ~ServiceTCPConfigure(){INFO("");}
  private:
    std::mutex fGlobalSetParamsBarrier;
};

//class ServiceTCPInfo:public VDaemonServiceTCP{
//};



#endif
