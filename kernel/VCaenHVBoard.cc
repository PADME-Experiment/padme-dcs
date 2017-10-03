#include "VCaenHVBoard.h"   //in c file
#include <caenlib/CAENHVWrapper.h>
#include"DrvCaenHV.h"
#include<vector>



  void
VCaenHVBoard::GetChParam(const std::string&par, void* res)
{
  std::vector<ushort> allch;
  allch.resize(fNumberOfChannels);
  for(int i=0;i<fNumberOfChannels;++i)allch[i]=i;
  CAENHV_GetChParam(std::dynamic_pointer_cast<DrvCaenHV>(GetParent())->GetCaenCrateHandle(),fSlotNumber, 
      par.c_str(), unsigned(fNumberOfChannels), &(*allch.begin()), res);
  INFO(par+std::to_string(res[0]));
}
