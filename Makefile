all:
	g++ -o ./build/automata src/alfabeto.cc src/automata.cc src/main.cc src/pilaDeSimbolos.cc

clean:
	rm -f ./build/automata