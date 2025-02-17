CC = g++
# Deploy flags
CF = -std=c++23 -Wall -O3 -funroll-loops -static -flto
# Development flags
CF = -std=c++23 -Wall -O0 -lstdc++   


clean:
	rm build/*
	rm spinfetch.bin
setup:
	mkdir build
fetch:
	git fetch
install: setup build
	cp spinfetch.bin /usr/local/bin/spinfetch
	mkdir $(HOME)/Desktop/spinfetch

update: clean fetch build
	rm -r releases/*
	mv /usr/local/bin/spinfetch releases/spinfetch.last
	cp spinfetch.bin /usr/local/bin/spinfetch


build: main.o console.o binary.o arginterpreter.o infofetch.o printer.o fileloader.o
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

printer.o:
	$(CC) $(CF) src/printer.cpp -c -o build/printer.o

fileloader.o:
	$(CC) $(CF) src/fileloader.cpp -c -o build/fileloader.o
