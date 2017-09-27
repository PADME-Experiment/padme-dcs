ccfiles=$(shell find kernel -name "*.cc")
hhfiles=$(shell find kernel -name "*.h")
kernel.exe: $(ccfiles) $(hhfiles)
	g++-5 $(ccfiles) -I. -Lcaenlib -lcaenhvwrapper -lc -o kernel.exe -DUNIX -lcaenhvwrapper -lncurses -lpthread -ldl -lm -std=c++11

HVcontrol.exe:
	g++ PadmeHV-tmp/HVcontrol.c  -I. -Lcaenlib -lcaenhvwrapper -lc -o HVcontrol.exe -DUNIX -I caenlib/ -lcaenhvwrapper -lncurses -lpthread -ldl -lm

