CC = g++
CFLAGS =-ICPLUS_INCLUDE_PATH -Wall -Ipart2/inc -Ipart3/inc
VPATH=src

YUKA_OBJS = yuka.o bytecode.o compiler.o parser.o vm.o

.PHONY: clean

yuka: $(YUKA_OBJS)
clean:
	@- $(RM) $(YUKA_OBJS)



