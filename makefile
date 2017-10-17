flags= -framework SDL2 -framework SDL2_image -framework SDL2_ttf

example1: rsdl.o examples/example1.cpp
		g++ src/rsdl.o examples/example1.cpp $(flags) -o example1.out

text_input: rsdl.o examples/textInput.cpp
		g++ src/rsdl.o examples/textInput.cpp $(flags) -o textInput.out		

rsdl.o: src/rsdl.cpp
		g++ -c src/rsdl.cpp -o src/rsdl.o
