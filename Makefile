CC = gcc
CFLAGS = -Wall -c -std=c99 -g -O3
OBJECTS = glalgebra.o

all: $(OBJECTS)

install: all
	ar -cvq libglalgebra.a $(OBJECTS)
	mv libglalgebra.a /usr/local/lib/
	mv glalgebra.h /usr/local/include/

clean:
	rm $(OBJECTS)