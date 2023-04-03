test: structure.o test.o user.o traitement.o matrices.o test_user.o test_traitement.o test_structure.o test_matrices.o
	gcc -g -static -o test structure.o test.o user.o traitement.o matrices.o test_user.o test_traitement.o test_structure.o test_matrices.o -Wall -lcunit

structure.o: ../structure.c
	gcc -g -c ../structure.c -lcunit

user.o: ../user.c
	gcc -g -c ../user.c -lcunit

traitement.o: ../traitement.c
	gcc -g -c ../traitement.c -lcunit

matrices.o: ../matrices.c
	gcc -g -c ../matrices.c -lcunit

test.o: test.c
	gcc -g -c test.c -lcunit

test_user.o: test_user.c
	gcc -g -c test_user.c -lcunit

test_traitement.o: test_traitement.c
	gcc -g -c test_traitement.c -lcunit

test_structure.o: test_structure.c
	gcc -g -c test_structure.c -lcunit

test_matrices.o: test_matrices.c
	gcc -g -c test_matrices.c -lcunit
 
clean:
	rm -f serveur test *.o 
