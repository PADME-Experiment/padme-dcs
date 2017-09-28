ccfiles=$(shell find kernel -name "*.cc")
hhfiles=$(shell find kernel -name "*.h")


.PHONY: kernel.exe
kernel.exe: $(ccfiles) $(hhfiles)
	g++ $(ccfiles) -I. -Lcaenlib -lc -o kernel.exe -DUNIX -lcaenhvwrapper -lncurses -lpthread -ldl -lm -g -O0

HVcontrol.exe:
	g++ PadmeHV-tmp/HVcontrol.c  -I. -Lcaenlib -lcaenhvwrapper -lc -o HVcontrol.exe -DUNIX -I caenlib/ -lcaenhvwrapper -lncurses -lpthread -ldl -lm

