serveur : structure.o serveur.o user.o fonctions.o matrices.o 
	gcc -g -static -o serveur structure.o serveur.o user.o fonctions.o matrices.o -Wall

structure.o: structure.c
	gcc -g -c structure.c

serveur.o: serveur.c
	gcc -g -c serveur.c

user.o: user.c
	gcc -g -c user.c

fonctions.o: fonctions.c
	gcc -g -c fonctions.c -lunistd

matrices.o: matrices.c
	gcc -g -c matrices.c
 
clean:
	rm -f serveur *.o

scp:
	scp serveur grpA4@192.168.200.13: