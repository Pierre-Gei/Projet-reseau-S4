client : client.o conversion.o
	gcc -g -static -o client client.o conversion.o -Wall

test :  test.o structure.o conversion.o
	gcc -g -static -o test test.o structure.o conversion.o -Wall -lcunit -lSDL2

structure.o: structure.c
	gcc -g -c structure.c -lSDL2 -Wall

conversion.o: conversion.c
	gcc -g -c conversion.c -lSDL2 -Wall

client.o: client.c
	gcc -g -c client.c -lSDL2 -Wall
	
clean:
	rm -f client test *.o