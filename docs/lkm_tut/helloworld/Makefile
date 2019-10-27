# Makefile for the helloworld kernel module

LINUX_ROOT	= /usr/src/linux
# The CFLAGS do the following:
#  -enable module versioning
#  -compile as a module
#  -tell the compiler where the kernel includes are located
#  -don't include the standard lib (doesn't exist in the kernel)
#  -include debugging symbols
#  -optimize (level 1)
CFLAGS		= -DMODVERSIONS \
				  -DMODULE \
				  -I$(LINUX_ROOT)/include \
				  -nostdinc \
				  -g \
				  -O1
OBJS			= helloworld.o
CC				= gcc

all: $(OBJS)


load: all
	insmod helloworld.o

unload:
	rmmod helloworld

clean:
	rm -f $(OBJS)

.PHONY: all load unload clean

