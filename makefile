UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
		# HEAD := $(shell cp src/sdlheaders/mac.hpp src/sdlHeaders.hpp)
		HEAD := $(shell echo "src/sdlheaders/mac.hpp" > ./src/sdlHeaders.hpp)
  	CCFLAGS= -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
		HEAD := $(shell cp src/sdlheaders/linux.hpp src/sdlHeaders.hpp)
		CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
endif

ifndef HEAD
	$(error Headers are not set)
endif

example1: rsdl.o examples/example1.cpp
		g++ src/rsdl.o examples/example1.cpp $(CCFLAGS) -o example1.out

text_input: rsdl.o examples/textInput.cpp
		g++ src/rsdl.o examples/textInput.cpp $(CCFLAGS) -o textInput.out

rsdl.o: src/rsdl.cpp
		g++ -c src/rsdl.cpp -o src/rsdl.o
