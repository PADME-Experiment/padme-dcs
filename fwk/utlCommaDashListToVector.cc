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

  std::vector<unsigned int>
utl::NumICommaDashListToVector(std::string str)
{
  if(str.find_first_not_of("0123456789,-")!=std::string::npos){
    throw fwk::Exception_tobefixed("CommaDashListToVector ");
  }
  std::vector<unsigned int> ret;
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




  int
utl::ExtractFirstPrefix(std::set<std::string>&in,std::set<std::string>&out,std::string& group)
{
  out.clear();
  auto init=in.begin();
  if(init==in.end())return 0;
  const auto& firstline=*init;
  group=firstline.substr(0,firstline.find_first_of(" ,/"));
  //if(group.size()==0){
  //  throw fwk::Exception_tobefixed("ExtractFirstPrefix syntax error: shouldn't start with slash");
  //}
  //if(firstline[group.size()]!='/'){
  //  throw fwk::Exception_tobefixed("ExtractFirstPrefix syntax error X/Y/Z_<- missing slash");
  //}
  long unsigned int numgrchan=group.size()+1; // +1 because of the '/'
  while(init!=in.end() &&
      init->find(group+"/")==0
      ){
    std::string line=init->substr(numgrchan);
    INFO(line);
    out.insert(line);
    in.erase(init);++init;
  }
  return out.size();
}
