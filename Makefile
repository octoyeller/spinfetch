CC = g++
CF = -std=c++23 -Wall


clean:
	rm build/*
setup:
	mkdir build
install: setup build
	cp spinfetch.bin /usr/local/bin/spinfetch



build: main.o console.o binary.o arginterpreter.o infofetch.o
	$(CC) $(CF) -o spinfetch.bin build/*


main.o:
	$(CC) $(CF) src/main.cpp -c -o build/main.o

console.o:
	$(CC) $(CF) src/console.cpp -c -o build/console.o

binary.o:
	$(CC) $(CF) src/binary.cpp -c -o build/binary.o

arginterpreter.o:
	$(CC) $(CF) src/arginterpreter.cpp -c -o build/arginterpreter.o

infofetch.o:
	$(CC) $(CF) src/infofetch.cpp -c -o build/infofetch.o
