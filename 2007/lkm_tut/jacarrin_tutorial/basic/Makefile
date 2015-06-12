basic.o: basic.c basic.h
	gcc -Wall -I/lib/modules/`uname -r`/build/include -c $< -O1 -g

.PHONY: clean
	
clean: 
	rm *.o

