client : client.o conversion.o affichage.o liaison.o
	gcc -g -o client client.o conversion.o affichage.o liaison.o -Wall -lSDL2

test :  test.o structure.o conversion.o affichage.o
	gcc -g -o test test.o structure.o conversion.o affichage.o -Wall -lcunit -lSDL2

structure.o: structure.c
	gcc -g -c structure.c -lSDL2 -Wall

conversion.o: conversion.c
	gcc -g -c conversion.c -lSDL2 -Wall

client.o: client.c
	gcc -g -c client.c -lSDL2 -Wall

affichage.o: affichage.c
	gcc -g -c affichage.c -lSDL2 -Wall

liaison.o: liaison.c
	gcc -g -c liaison.c -lSDL2 -Wall
clean:
	rm -f client test *.o