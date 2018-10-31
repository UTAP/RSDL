UNAME_S := $(shell uname -s)
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf

all: test.out example.out

test.out: main.o textInput.o myString.o rsdl.o
	g++ main.o rsdl.o textInput.o myString.o $(CCFLAGS) -o test.out

example.out: example.o rsdl.o
	g++ example.o rsdl.o $(CCFLAGS) -o example.out

example.o: src/rsdl.hpp example/example.cpp
	g++ -c example/example.cpp -o example.o

main.o: src/rsdl.hpp example/textInput.hpp example/myString.hpp example/main.cpp
	g++ -c example/main.cpp -o main.o

textInput.o: src/rsdl.hpp example/textInput.hpp example/myString.hpp example/textInput.cpp
	g++ -c example/textInput.cpp -o textInput.o

myString.o: example/myString.hpp src/rsdl.hpp example/myString.cpp
		g++ -c example/myString.cpp -o myString.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	g++ -c src/rsdl.cpp -o rsdl.o

.PHONY: clean
clean:
	rm -r *.o