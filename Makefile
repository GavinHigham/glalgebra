CC = gcc
CFLAGS = -Wall -c -std=c99 -O3
OBJECTS = glalgebra.o
RED   = '\033[0;31m'
GREEN = '\033[0;32m'
NOCOL = '\033[0m'

all: $(OBJECTS)

install: all
	ar -cvq libglalgebra.a $(OBJECTS)
	mv libglalgebra.a /usr/local/lib/
	cp glalgebra.h /usr/local/include/

test: glalgebra_test.c glalgebra.c glalgebra.h
	$(CC) glalgebra_test.c glalgebra.o -o glalgebra_test
	@if ./glalgebra_test; then echo -e "${GREEN}Tests succeeded.${NOCOL}"; else echo -e "${RED}Tests failed.${NOCOL}"; fi

clean:
	rm $(OBJECTS)
