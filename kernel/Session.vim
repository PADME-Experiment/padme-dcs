let &path = &path . "," . "/home/georgieff/git/padme-dcs/"

edit ./Session.vim
vsplit .

tabnew VDeviceDriver.h
vsplit VDeviceDriver.cc
vsplit VValue.h
vsplit VValue.cc
vsplit VDaemon.h
vsplit VDaemon.cc

tabnew DrvCaenHV.h
vsplit DrvCaenHV.cc
vsplit DrvCaenSY4527.h
vsplit DrvCaenSY4527.cc

tabnew VCaenHVBoard.h
vsplit VCaenHVBoard.cc
vsplit DrvCaenA7030.h
vsplit DrvCaenA7030.cc

tabnew kernel.h
vsplit kernel.cc

tabnew DeviceManager.h
vsplit DeviceManager.cc

tabnew ../fwk/utlCommaDashListToVector.h
vsplit ../fwk/utlCommaDashListToVector.cc
vsplit ../test.cc

tabnew ../PadmeHV-tmp/HVcontrol.c
vsplit ../PadmeHV-tmp/HVcontrol.h
vsplit ../Documentation-tmp/CAENHVWrapper-5.82/include/CAENHVWrapper.h
