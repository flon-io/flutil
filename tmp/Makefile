
CFLAGS=-I../src
LDLIBS=
CC=c99
VPATH=../src

# TODO: at some point deploy rodzo and help deploy it
RODZO=../../rodzo/bin/rodzo


s.c: ../spec/*_spec.c
	$(RODZO) ../spec -o s.c

s: $(NAME).o

spec: s
	time ./s

vspec: s
	valgrind --leak-check=full -v ./s

clean:
	rm -f *.o
	rm -f *.so
	rm -f *.c
	rm -f s

.PHONY: spec vspec clean
