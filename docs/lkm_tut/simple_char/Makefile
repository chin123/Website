# Makefile for the simple_char kernel module

LINUX_ROOT	= /usr/src/linux
# The CFLAGS do the following:
#  -enable module versioning
#  -compile as a module
#  -tell the compiler where the kernel includes are located
#  -include debugging symbols
#  -optimize (level 1)
CFLAGS		= -DMODVERSIONS \
				  -DMODULE \
				  -I$(LINUX_ROOT)/include \
				  -g \
				  -O1
OBJS			= simple_char.o
CC				= gcc

all: $(OBJS)


load: all
	insmod simple_char.o

unload:
	rmmod simple_char

clean:
	rm -f $(OBJS)

.PHONY: all load unload clean


