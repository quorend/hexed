CC = gcc -g -I lib

OBJFILES = \
build/main.o \
build/CuTest.o

.PHONY: all
all: build/hexed

build/hexed: build $(OBJFILES)
	$(CC) -o build/hexed $(OBJFILES)

.PHONY: build
build:
	mkdir -p build

build/main.o: src/main.c
	$(CC) -o build/main.o -c src/main.c

build/CuTest.o: lib/cutest/CuTest.c lib/cutest/CuTest.h
	$(CC) -o build/CuTest.o -c lib/cutest/CuTest.c

.PHONY: clean
clean:
	rm build/*

.PHONY: tidy
tidy:
	rm *~ src/*~
