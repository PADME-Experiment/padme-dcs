#include "VDaemon.h"   //in c file


  void
VDaemon::Daemonize()
{
  fRun=true;
 // fThread=new 
  std::thread (&VDaemon::StartCycling,this).detach();
}

  void
VDaemon::StartCycling()
{
  OnStart();
  while(fRun){
    OnCycle();
  }
  OnStop();
}

  void
VDaemon::Kill()
{
  fRun=false;
}
