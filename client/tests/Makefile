test :  test.o structure.o conversion.o affichage.o liaison.o test_affichage.o test_conversion.o 
	gcc -g -o test test.o structure.o conversion.o affichage.o liaison.o test_affichage.o test_conversion.o -Wall -lcunit -lSDL2 -lSDL2_ttf

structure.o: ../structure.c
	gcc -g -c ../structure.c -lSDL2 -Wall

conversion.o: ../conversion.c
	gcc -g -c ../conversion.c -lSDL2 -Wall

affichage.o: ../affichage.c
	gcc -g -c ../affichage.c -lSDL2 -lSDL2_ttf  -Wall

liaison.o: ../liaison.c
	gcc -g -c ../liaison.c -lSDL2 -Wall

test_affichage.o: test_affichage.c
	gcc -g -c test_affichage.c -lSDL2 -lSDL2_ttf -Wall -lcunit

test_conversion.o: test_conversion.c
	gcc -g -c test_conversion.c -lSDL2 -Wall -lcunit

clean:
	rm -f test *.o