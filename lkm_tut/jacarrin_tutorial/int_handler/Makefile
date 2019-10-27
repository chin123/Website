CFLAGS = -I/lib/modules/`uname -r`/build/include -g

all: catchDebugExceptions.o

%.o: %.S
	$(CC) -c -D__ASSEMBLY__ $(CFLAGS) -o $@ $<

catchDebugExceptions.o: trap.o entry.o
	$(LD) -r -o $@  $^

clean:
	rm -f *.o 

.PHONY: clean
