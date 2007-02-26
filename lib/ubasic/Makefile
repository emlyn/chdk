topdir=../../

include $(topdir)makefile.inc

all: libubasic.a

libubasic.a: camera_functions.o tokenizer.o  ubasic.o

check:
	gcc -Wall -DTEST -o test *.c

clean:
	rm -f *.o *.a test
