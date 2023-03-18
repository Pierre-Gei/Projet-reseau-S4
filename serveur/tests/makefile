test: structure.o test.o user.o fonctions.o matrices.o test_user.o test_fonctions.o test_structure.o
	gcc -g -static -o test structure.o test.o user.o fonctions.o matrices.o test_user.o test_fonctions.o test_structure.o -Wall -lcunit

structure.o: ../structure.c
	gcc -g -c ../structure.c -lcunit

user.o: ../user.c
	gcc -g -c ../user.c -lcunit

fonctions.o: ../fonctions.c
	gcc -g -c ../fonctions.c -lcunit

matrices.o: ../matrices.c
	gcc -g -c ../matrices.c -lcunit

test.o: test.c
	gcc -g -c test.c -lcunit

test_user.o: test_user.c
	gcc -g -c test_user.c -lcunit

test_fonctions.o: test_fonctions.c
	gcc -g -c test_fonctions.c -lcunit

test_structure.o: test_structure.c
	gcc -g -c test_structure.c -lcunit
 
clean:
	rm -f serveur test *.o 
