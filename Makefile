ccfiles=$(shell find kernel -name "*.cc")
ccfwkfiles=$(shell find fwk -name "*.cc")
hhfiles=$(shell find kernel -name "*.h")


.PHONY: kernel.exe doxygen
kernel.exe: $(ccfiles) $(hhfiles)
	g++ $(ccfiles) $(ccfwkfiles) -I. -Lkernel/extern/lib -lc -o kernel.exe -DUNIX -lcaenhvwrapper -lncurses -lpthread -ldl -lm -g -O0 -lyaml-cpp -Wpedantic
doxygen:
	cd docs;doxygen

HVcontrol.exe:
	g++ PadmeHV-tmp/HVcontrol.c  -I. -Lcaenlib -lcaenhvwrapper -lc -o HVcontrol.exe -DUNIX -I caenlib/ -lcaenhvwrapper -lncurses -lpthread -ldl -lm

