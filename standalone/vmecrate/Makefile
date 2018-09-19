ccfiles=$(shell find -name "*.cc")


.PHONY: all
.DEFAULT_GOAL: all

all: V8100_mon_ALL.exe V8100_set_off.exe V8100_set_on.exe
%.exe: %.cc
	echo $<
	g++ $< -o $@ -I. -L../../kernel/extern/lib -I ../../kernel/extern/ -I ../../kernel/extern/  -I ../../kernel/extern/V8100/V8100SDK/  -I ../../kernel/extern/V8100/common/ -lc -DUNIX  -lV8100SDK -lncurses -lpthread -ldl -lm -g -O0 -Wpedantic -DLINUX -D__GCC
