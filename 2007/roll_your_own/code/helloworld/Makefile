#Note: this makefile doesn't suck and shouldn't require gmake like old versions did

CC = gcc
LD = ld

CFLAGS = -g -O -I.

OBJS = main.o
 
KERNELFN = kernel.elf
FLOPPY_IMG = helloworld.img

$(FLOPPY_IMG): $(KERNELFN)
	./bootmaker helloworld.ini $@ -floppy

$(KERNELFN): $(OBJS)
	$(LD) -o $@ $(OBJS) -dN -Ttext 0x101080 

clean:
	rm -f $(OBJS) $(KERNELFN) $(FLOPPY_IMG)

