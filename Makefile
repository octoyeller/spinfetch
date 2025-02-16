CC = g++
CF = -std=c++23 -Wall


clean:
	rm build/*

build: main.o console.o binary.o
	$(CC) $(CF) -o spinfetch.bin build/*


main.o:
	$(CC) $(CF) src/main.cpp -c -o build/main.o

console.o:
	$(CC) $(CF) src/console.cpp -c -o build/console.o

binary.o:
	$(CC) $(CF) src/binary.cpp -c -o build/binary.o
