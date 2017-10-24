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
  if(fThread==nullptr){
    ERROR("not threaded");
    return;
  }
  fRun=false;
  INFO("will join");
  fThread->join();
  INFO("will delete");
  delete fThread;
  INFO("deleted");
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
VDaemonServiceTCP::AssertInit()
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
  if(fServiceSocket==-1){ ERROR("socket=-1"); return; }

  int x=1;
  if(-1==
      setsockopt(fServiceSocket, SOL_SOCKET, SO_REUSEADDR,&x, sizeof(x))
    ) { ERROR("setsockopt=-1"); return; }



  if(-1==
      bind(fServiceSocket, servinfo->ai_addr, servinfo->ai_addrlen)
    ) { ERROR("bindresult=-1"); return; }
  freeaddrinfo(servinfo); // free the linked-list
  if(-1==
      listen(fServiceSocket,10)
    ) { ERROR("listen=-1"); return; }
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

//  void
//VDaemonServiceTCP::ServiceLoop(const int fd)
//{
//  // FIXME this function should be pure virtual
//  // this is an example only
//  std::string received;
//  while(received.find("bye",0,3)==std::string::npos){
//    received.clear();
//    char buf[200];
//    int len=recv(fd,buf,sizeof(buf),0);
//    received.append(buf,len);
//    while(received.back()!='\n'){
//      int len=recv(fd,buf,sizeof(buf),0);
//      received.append(buf,len);
//    }
//    received.erase (received.end()-2, received.end());
//    int sentbytes=send(fd,received.data(),received.size(),0);
//
//    SUCCESS(received+"  size  "+std::to_string(received.size()));
//
//  }
//}

#include"DeviceManager.h"
#include<sstream>
#include <algorithm>

  void
ServiceTCPConfigure::ServiceLoop(const int fd)
{
  int sentbytes;
  char buf[5];
  int len;

  std::string tcpcurrent;
  do{
    std::set<std::string> listOfCmds;
    tcpcurrent="";
    std::string tcpbuffer;
    do{
      len=recv(fd,buf,sizeof(buf),0);
      tcpbuffer.append(buf,len);
      std::replace(tcpbuffer.begin(),tcpbuffer.end(),'\r', '#');
      while(tcpbuffer.find("\n")!=std::string::npos){
        const size_t firstBSn=tcpbuffer.find("\n");
        tcpcurrent=tcpbuffer.substr(0,firstBSn-1); // -1 because of \r
        tcpbuffer.erase(0,firstBSn+1);
        //INFO("insert "+tcpcurrent);
        if(tcpcurrent=="bye"||tcpcurrent=="do")break;
        listOfCmds.insert(tcpcurrent);
        //INFO("ADD " +tcpcurrent);
      }
    }while(len>=0&&tcpcurrent!="bye"&&tcpcurrent!="do"); //empty line to execute

    std::string tmpstr;
    try{
      sentbytes=0;
      tmpstr="Processing . . .\r\n";
      send(fd,tmpstr.data(),tmpstr.size(),0);
      //do{ // tova nesho cikli....
      //  sentbytes+=send(fd,tmpstr.substr(sentbytes).data(),tmpstr.size()-sentbytes,0);
      //}while(sentbytes==tmpstr.size());
      { // This block defines the mutex scope
        // Multiple clients may be connected. Use of mutex
        // might be an overkill but is definitely safer!
        std::lock_guard<std::mutex> guard(fGlobalSetParamsBarrier);
        DeviceManager::GetInstance().SetParams(listOfCmds);
      }
      tmpstr="DONE\r\n\r\n";
      sentbytes=send(fd,tmpstr.data(),tmpstr.size(),0);
    }
    //catch(const fwk::Exception&e){//FIXME
    catch(const std::exception&e){//FIXME
      tmpstr=std::string(e.what())+"\n\n";
      sentbytes=send(fd,tmpstr.data(),tmpstr.size(),0);
    }
  }while(tcpcurrent!="bye");
}



  void
ServiceTCPInfo::ServiceLoop(const int fd)
{
  int sent_b;
  do{
    std::stringstream ss;
    DeviceManager::GetInstance().GetInfoAll(ss);
    std::string str;
    while(std::getline(ss,str)){
      INFO(str);
      sent_b=send(fd,str.data(),str.size(),0);
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }while(sent_b>=0);
}
