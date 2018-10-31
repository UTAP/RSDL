UNAME_S := $(shell uname -s)
CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf

all: test.out example.out

test.out: main.o textInput.o myString.o rsdl.o
	$(CC) main.o rsdl.o textInput.o myString.o $(CCFLAGS) -o test.out

example.out: example.o rsdl.o
	$(CC) example.o rsdl.o $(CCFLAGS) -o example.out

example.o: src/rsdl.hpp example/example.cpp
	$(CC) -c example/example.cpp -o example.o

main.o: src/rsdl.hpp example/textInput.hpp example/myString.hpp example/main.cpp
	$(CC) -c example/main.cpp -o main.o

textInput.o: src/rsdl.hpp example/textInput.hpp example/myString.hpp example/textInput.cpp
	$(CC) -c example/textInput.cpp -o textInput.o

myString.o: example/myString.hpp src/rsdl.hpp example/myString.cpp
	$(CC) -c example/myString.cpp -o myString.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	$(CC) -c src/rsdl.cpp -o rsdl.o

.PHONY: clean
clean:
	rm -r *.o