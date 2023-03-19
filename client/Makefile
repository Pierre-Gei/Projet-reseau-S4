client : client.o conversion.o
	gcc -g -static -o client client.o conversion.o -Wall
test : test.o conversion.o
	gcc -g -static -o test test.o conversion.o -Wall -lcunit

conversion.o: conversion.c
	gcc -g -c conversion.c

client.o: client.c
	gcc -g -c client.c

clean:
	rm -f client test *.o