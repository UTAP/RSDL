UNAME_S := $(shell uname -s)
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf

all: test.out rsdl.o

test.out: main.o textInput.o myString.o rsdl.o
	g++ main.o rsdl.o textInput.o myString.o $(CCFLAGS) -o test.out

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