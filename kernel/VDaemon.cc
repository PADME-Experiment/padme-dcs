#include "VDaemon.h"   //in c file
#include "fwk/utlMessageBus.h"


  void
VDaemonSingleThread::Daemonize()
{
  INFO("");
  fRun=true;
  INFO("will start");
 fThread=new std::thread (&VDaemonSingleThread::StartCycling,this);
  INFO("started");
}

  void
VDaemonSingleThread::StartCycling()
{
  OnStart();
  while(fRun){
    OnCycle();
  }
  OnStop();
}

  void
VDaemonSingleThread::JoinThread()
{
  fRun=false;
  fThread->join();
  delete fThread;
}

  void
VDaemonSingleThread::KillThread()
{
  fRun=false;
  fThread->detach();
  delete fThread;
}
