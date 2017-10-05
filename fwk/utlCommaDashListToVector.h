#ifndef  _DCS_fwk_utlCommaDashListToVector_h_
#define  _DCS_fwk_utlCommaDashListToVector_h_ 1

#include<string>
#include<vector>
#include<set>
#include<cstdint>

namespace utl{
  std::vector<uint32_t>    NumICommaDashListToVector  (std::string str);
  std::vector<float>       NumFCommaDashListToVector  (std::string str);
  std::vector<std::string> StringCommaDashListToVector(std::string str);
  int ExtractFirstPrefix(std::set<std::string>&in,std::set<std::string>&out,std::string& group);
}

#endif
