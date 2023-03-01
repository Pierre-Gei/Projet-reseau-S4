serveur : serveur.o user.o fonctions.o
	gcc -o serveur serveur.o user.o fonctions.o -Wall

serveur.o: serveur.c
	gcc -c serveur.c

user.o: user.c
	gcc -c user.c

fonctions.o: fonctions.c
	gcc -c fonctions.c

clean:
	rm -f main main.o