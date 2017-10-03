#include "VDaemon.h"   //in c file


  void
VDaemonSingleThread::Daemonize()
{
  fRun=true;
 // fThread=new 
  std::thread (&VDaemonSingleThread::StartCycling,this).detach();
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
VDaemonSingleThread::Kill()
{
  fRun=false;
}
