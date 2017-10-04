#include "utlCommaDashListToVector.h"   //in c file
#include "utlMessageBus.h"
#include "fwkException.h"

  std::vector<std::string>
utl::StringCommaDashListToVector(std::string str)
{
  std::vector<std::string> ret;
  int from=0;int to=0;
  while((to=str.find_first_of(",",from+1))!=std::string::npos){
    int to2=str.find_first_of(",",to+1);
    std::string left,right;
    left=str.substr(from,to-from);
    right=str.substr(to+1,to2-to-1);
    ret.push_back(left);
    if((str.find_first_of(",",to+1))==std::string::npos){
      ret.push_back(right);
    }
    from=to+1;
  }
  return ret;
}

  std::vector<float>
utl::NumFCommaDashListToVector(std::string str)
{
  if(str.find_first_not_of("0123.456789,")!=std::string::npos){
    throw fwk::Exception_tobefixed("CommaDashListToVector: unexpected symbols found");
  }
  std::vector<float> ret;
  int from=0;int to=0;
  while((to=str.find_first_of(",",from+1))!=std::string::npos){
    int to2=str.find_first_of(",",to+1);
    float left,right;
    try{
      left=std::stof(str.substr(from,to-from));
      right=std::stof(str.substr(to+1,to2-to-1));
    }catch(...){
      ERROR("exceptions are not expected.");
      throw;
    }
    if(str[to]==','){
      ret.push_back(left);
    }else ERROR("What else could it be???");
    if((str.find_first_of(",",to+1))==std::string::npos){
      ret.push_back(right);
    }
    from=to+1;
  }
  return ret;
}

  std::vector<int>
utl::NumICommaDashListToVector(std::string str)
{
  if(str.find_first_not_of("0123456789,-")!=std::string::npos){
    throw fwk::Exception_tobefixed("CommaDashListToVector ");
  }
  std::vector<int> ret;
  int from=0;int to=0;
  while((to=str.find_first_of(",-",from+1))!=std::string::npos){
    int to2=str.find_first_of(",-",to+1);
    int left,right;
    try{
      left=std::stoi(str.substr(from,to-from));
      right=std::stoi(str.substr(to+1,to2-to-1));
    }catch(...){
      ERROR("exceptions are not expected.");
      throw;
    }
    if(left>=right){
      throw fwk::Exception_tobefixed("CommaDashListToVector values should be ordered");
    }
    if(str[to]==','){
      ret.push_back(left);
    }else if(str[to]=='-'){
      for(int i=left;i<right;++i){
        ret.push_back(i);
      }
    }else ERROR("What else could it be???");
    if((str.find_first_of(",-",to+1))==std::string::npos){
      ret.push_back(right);
    }
    from=to+1;
  }
  return ret;
}
