UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CCFLAGS= -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
	CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
endif

all: test rsdl.o

test: textInput.o myString.o rsdl.o
	g++ example/main.cpp rsdl.o textInput.o myString.o $(CCFLAGS) -o test.out

textInput.o: example/textInput.cpp myString.o rsdl.o
	g++ -c example/textInput.cpp -o textInput.o

myString.o: example/myString.cpp rsdl.o
		g++ -c example/myString.cpp -o myString.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	g++ -c src/rsdl.cpp -o rsdl.o

clean:
	rm -r *.o