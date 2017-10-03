#include "VDaemon.h"   //in c file


  void
VDaemonSingleThread::Daemonize()
{
  fRun=true;
 fThread=new std::thread (&VDaemonSingleThread::StartCycling,this);
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
