UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
		HEAD := \"sdlheaders/mac.hpp\"
  	CCFLAGS= -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
		HEAD := \"sdlheaders/linux.hpp\"
		CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
endif

all: text_input rsdl.o head


example4: head rsdl.o examples/example4.cpp
		g++ src/rsdl.o examples/example4.cpp $(CCFLAGS) -o example4.out

example3: head rsdl.o examples/example3.cpp
		g++ src/rsdl.o examples/example3.cpp $(CCFLAGS) -o example3.out

example2: head rsdl.o examples/example2.cpp
		g++ src/rsdl.o examples/example2.cpp $(CCFLAGS) -o example2.out

example1: head rsdl.o examples/example1.cpp
		g++ src/rsdl.o examples/example1.cpp $(CCFLAGS) -o example1.out

text_input: rsdl.o examples/textInput.cpp
		g++ src/rsdl.o examples/textInput.cpp $(CCFLAGS) -o textInput.out

rsdl.o: src/rsdl.cpp
		g++ -c src/rsdl.cpp -o src/rsdl.o
head:
		echo "#include "$(HEAD) > ./src/sdlHeaders.hpp
