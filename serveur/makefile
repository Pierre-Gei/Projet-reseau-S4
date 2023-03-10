serveur : structure.o serveur.o user.o fonctions.o
	gcc -o serveur structure.o serveur.o user.o fonctions.o -Wall

structure.o: structure.c
	gcc -c structure.c

serveur.o: serveur.c
	gcc -c serveur.c

user.o: user.c
	gcc -c user.c

fonctions.o: fonctions.c
	gcc -c fonctions.c -lunistd
 
clean:
	rm -f main main.o