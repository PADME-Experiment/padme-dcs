#ifndef _DCS_fwkException_hh_
#define _DCS_fwkException_hh_ 1
#include<typeinfo>
#include<string>

/**
 * This is a example header file
 * class MessageBus_except:public fwk::Exception{
 *   public:
 *     MessageBus_except(){fType="MessageBus_except";}
 *     MessageBus_except& CannotCreateFile(const std::string&fn);
 *     MessageBus_except& UnknownMessageType(MessageBus::eMessageType&);
 * };
 */

/**
 * This is a example cc file
 *   utl::MessageBus_except&
 * utl::MessageBus_except::CannotCreateFile(const std::string&fn)
 * {
 *   fWhat="File '"+fn+"' cannot be created.";
 *   return *this;
 * }
 *   utl::MessageBus_except&
 * utl::MessageBus_except::UnknownMessageType(utl::MessageBus::eMessageType& mt)
 * {
 *   fWhat="Message type '"+std::to_string(int(mt))+"' is unknown";
 *   return *this;
 * }
 */



namespace fwk{
  class Exception:public std::exception{
    public:
      const char* what() const noexcept {return fWhat.c_str();}
      const std::string& GetWhat()const noexcept{return fWhat;}
      const std::string& GetType()const noexcept{return fType;}
    protected:
      virtual ~Exception(){}
      void SetType(Exception& a){fType=typeid(a).name();}
      std::string fWhat;
      std::string fType;
  };
}

#endif
