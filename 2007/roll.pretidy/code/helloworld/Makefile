# NOTE: use gmake for this Makefile

PRE = /develop/xdev/bin/
GCC = $(PRE)gcc386
G++ = $(PRE)g++386
LD = $(PRE)ld386

OBJS = main.o
 
 KERNELFN = kernel.elf

$(KERNELFN): $(OBJS)
	$(LD) -o $@ $(OBJS) -dN -Ttext 0x101080 

.cc.o: 
	$(G++) -O -I. -c -o $@ $< 

.cc.s:
	$(G++) -O -I. -S -o $@ $<

.c.o:
	$(GCC) -O -I. -c -o $@ $<

.c.s:
	$(GCC) -O -I. -S -o $@ $<

.S.o:
	$(GCC) -c -o $@ $<

clean:
	rm $(OBJS) $(KERNELFN)
