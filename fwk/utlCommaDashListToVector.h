#ifndef  _DCS_fwk_utlCommaDashListToVector_h_
#define  _DCS_fwk_utlCommaDashListToVector_h_ 1

#include<string>
#include<vector>

namespace utl{
  std::vector<int>         NumICommaDashListToVector  (std::string str);
  std::vector<float>       NumFCommaDashListToVector  (std::string str);
  std::vector<std::string> StringCommaDashListToVector(std::string str);
}

#endif
