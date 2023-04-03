serveur : structure.o serveur.o user.o traitement.o matrices.o 
	gcc -g -static -o serveur structure.o serveur.o user.o traitement.o matrices.o -Wall

structure.o: structure.c
	gcc -g -c structure.c

serveur.o: serveur.c
	gcc -g -c serveur.c

user.o: user.c
	gcc -g -c user.c

traitement.o: traitement.c
	gcc -g -c traitement.c

matrices.o: matrices.c
	gcc -g -c matrices.c
 
clean:
	rm -f serveur test *.o 

scp:
	scp serveur pixelwar: