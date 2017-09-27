ccfiles=$(shell find kernel -name "*.cc")
hhfiles=$(shell find kernel -name "*.h")
kernel.exe: $(ccfiles) $(hhfiles)
	g++ $(ccfiles) -I. -Lcaenlib -lcaenhvwrapper -lc -o kernel.exe -DUNIX

HVcontrol.exe:
	g++ PadmeHV-tmp/HVcontrol.c  -I. -Lcaenlib -lcaenhvwrapper -lc -o HVcontrol.exe -DUNIX -I caenlib/

