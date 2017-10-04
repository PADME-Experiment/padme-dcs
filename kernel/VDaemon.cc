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











  void
VDaemonService::Daemonize()
{
  //std::lock_guard<std::mutex> lock(fDaemonizeBarrier);
  std::thread thr(&VDaemonService::Service,this);
  thr.detach();
  //fThreads.push_back(std::make_unique<std::thread>(&VDaemonService::Service,this));
}
  void
VDaemonService::KillAll()
{
  //for(std::list<std::unique_ptr<std::thread>>::iterator l_it=fThreads.begin();l_it!=fThreads.end();++l_it){
  //  (*l_it).get()->detach();
  //  //fThreads.erase(l_it);
  //}
}


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring> // memset
#include <unistd.h> //close


  void
VDaemonServiceTCP::Initialize()
{
  struct addrinfo hints;
  struct addrinfo *servinfo;
  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
  hints.ai_flags = AI_PASSIVE; // fill in my IP for me

  if(getaddrinfo(NULL, std::to_string(fPort).c_str(), &hints, &servinfo)!=0){
    ERROR("executing getaddrinfo");
    return;
  }

  fServiceSocket= socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if(fServiceSocket==-1){
    ERROR("socket=-1");
    return;
  }

  bind(fServiceSocket, servinfo->ai_addr, servinfo->ai_addrlen);
  freeaddrinfo(servinfo); // free the linked-list
  listen(fServiceSocket,10);
  INFO("");
}

  void
VDaemonServiceTCP::Finalize()
{
  close(fServiceSocket);
  INFO("");
}

  void
VDaemonServiceTCP::Service()
{
  INFO("");
  struct sockaddr_storage their_addr;
  socklen_t addr_size=sizeof(their_addr);
  int new_fd = accept(fServiceSocket, (struct sockaddr *)&their_addr, &addr_size);
  Daemonize();
  ServiceLoop(new_fd);
  close(new_fd);
}

  void
VDaemonServiceTCP::ServiceLoop(const int fd)
{
  // FIXME this function should be pure virtual
  // this is an example only
  std::string buf;
  buf.resize(10000,0);
  while(buf.find("bye",0,3)){
    int len=recv(fd,&(*buf.begin()),buf.size(),0);
    std::string received=buf.substr(0,len-2);
    SUCCESS(received+"  size  "+std::to_string(received.size()));

  }
}
