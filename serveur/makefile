serveur : structure.o serveur.o user.o fonctions.o matrices.o 
	gcc -g -static -o serveur structure.o serveur.o user.o fonctions.o matrices.o -Wall

structure.o: structure.c
	gcc -g -c structure.c -lcunit

serveur.o: serveur.c
	gcc -g -c serveur.c -lcunit

user.o: user.c
	gcc -g -c user.c -lcunit

fonctions.o: fonctions.c
	gcc -g -c fonctions.c -lcunit

matrices.o: matrices.c
	gcc -g -c matrices.c -lcunit
 
clean:
	rm -f serveur test *.o 

scp:
	scp serveur pixelwar: