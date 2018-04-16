UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
		HEAD := \"sdlheaders/mac.hpp\"
  	CCFLAGS= -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
		HEAD := \"sdlheaders/linux.hpp\"
		CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
endif

all: test rsdl.o head

test: textInput.o myString.o rsdl.o
		g++ example/main.cpp src/rsdl.o example/textInput.o example/myString.o $(CCFLAGS) -o test

textInput.o: example/textInput.cpp myString.o rsdl.o
	g++ -c example/textInput.cpp -o example/textInput.o

myString.o: example/myString.cpp rsdl.o
	g++ -c example/myString.cpp -o example/myString.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
		g++ -c src/rsdl.cpp -o src/rsdl.o

head:
		echo "#include "$(HEAD) > ./src/sdlHeaders.hpp
clean:
	rm -r *.o
