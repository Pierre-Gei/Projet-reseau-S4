serveur : structure.o serveur.o user.o fonctions.o matrices.o 
	gcc -static -o serveur structure.o serveur.o user.o fonctions.o matrices.o -Wall

structure.o: structure.c
	gcc -c structure.c

serveur.o: serveur.c
	gcc -c serveur.c

user.o: user.c
	gcc -c user.c

fonctions.o: fonctions.c
	gcc -c fonctions.c -lunistd

matrices.o: matrices.c
	gcc -c matrices.c
 
clean:
	rm -f serveur *.o

scp:
	scp serveur grpA4@192.168.200.13: