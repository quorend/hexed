CC = gcc -g -I lib -Wall -Werror

OBJCOMMON = \
build/CuTest.o \
build/file-access.o \
build/buffer.o \
build/display.o

OBJBUILD = \
build/main.o \
$(OBJCOMMON)

OBJTEST = \
test/build/main.o \
$(OBJCOMMON)

# Build targets
.PHONY: all
all: build/hexed test/build/tests runtests

.PHONY: runtests
runtests: build/hexed test/build/tests
	./test/build/tests

build/hexed: build $(OBJBUILD)
	$(CC) -o build/hexed $(OBJBUILD)

test/build/tests: test/build $(OBJTEST)
	$(CC) -o test/build/tests $(OBJTEST)

# Build directories
.PHONY: build
build:
	mkdir -p build

.PHONY: test/build
test/build:
	mkdir -p test/build

# Object files
build/main.o: src/main.c
	$(CC) -o build/main.o -c src/main.c

build/CuTest.o: lib/cutest/CuTest.c lib/cutest/CuTest.h
	$(CC) -o build/CuTest.o -c lib/cutest/CuTest.c

build/file-access.o: src/file-access.c src/file-access.h
	$(CC) -o build/file-access.o -c src/file-access.c

build/buffer.o: src/buffer.c src/buffer.h
	$(CC) -o build/buffer.o -c src/buffer.c

build/display.o: src/display.c src/display.h
	$(CC) -o build/display.o -c src/display.c

test/build/main.o: test/main.c
	$(CC) -o test/build/main.o -c test/main.c

# Housekeeping
.PHONY: clean
clean:
	rm build/* test/build/*

.PHONY: tidy
tidy:
	rm *~ src/*~ test/*~
