#include"utlMessageBus.h"

#include<sstream>
#include<string>
#include<typeinfo>

#include<ctime>
#include<iomanip>

  utl::MessageBus_except&
utl::MessageBus_except::CannotCreateFile(const std::string&fn)
{
  fWhat="File '"+fn+"' cannot be created.";
  return *this;
}
  utl::MessageBus_except&
utl::MessageBus_except::UnknownMessageType(utl::MessageBus::eMessageType& mt)
{
  fWhat="Message type '"+std::to_string(int(mt))+"' is unknown";
  return *this;
}

  utl::MessageBus&
utl::MessageBus::GetInstance()
{
    //std::lock_guard<std::mutex> lock(fGetInstanceBarrier);
  static MessageBus a;
  return a;
}

  void
utl::MessageBus::TypeOfString()
{
  std::cout<<typeid(std::string).name()<<std::endl;
  INFO(typeid(std::string).name());
}

  void
utl::MessageBus::SetLogFile(const std::string& fn)
{
  if(fn.size()==0)return;
  fFile.open(fn);
  if(!fFile.is_open()) throw MessageBus_except().CannotCreateFile(fn);
}



  void
utl::MessageBus::NewMessage(
    utl::MessageBus::eMessageType t,
    unsigned int l,
    const std::string& mes)
{
    std::lock_guard<std::mutex> lock(fNewMessageBarrier);
  std::stringstream timePref;
  if(fTimeFormat.size()>0){
    std::time_t t=std::time(nullptr);
    if(fUseLocalTime)
      timePref<<"\e[36m"<<std::put_time(std::localtime(&t),fTimeFormat.c_str())<<"\e[0m"<<"  ";
    else
      timePref<<"\e[36m"<<std::put_time(std::gmtime   (&t),fTimeFormat.c_str())<<"\e[0m"<<"  ";
  }

  std::string pref;
  switch (t){
    case eMessageType::eSuccess   :
      pref="\e[1;32m[SUCC]\e[0m  ";
      break;
    case eMessageType::eInfo      :
      pref="\e[1;34m[INFO]\e[0m  ";
      break;
    case eMessageType::eWarning   :
      pref="\e[1;33m[WARN]\e[0m  ";
      break;
    case eMessageType::eError     :
      pref="\e[1;31m[ERROR]\e[0m ";
      break;
    case eMessageType::eFatalError:
      pref="\e[1;31m[FATAL]\e[0m ";
      break;
    //case eMessageType::eException:
    //  pref="\e[0;35m[EXCEP]\e[0m ";
    //  break;
      //default:
      //  throw utl::MessageBus_except().UnknownMessageType(t);
  }
  if(l<=fDebugLevel){
    std::cerr
      <<timePref.str()
      <<pref
      <<mes
      <<std::endl
      <<std::flush;
  }
  if(fFile.is_open()){
    fFile
      <<timePref.str()
      <<pref
      <<mes
      <<std::endl;
  }
}
