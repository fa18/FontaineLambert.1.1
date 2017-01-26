clean :
	rm -f *.o

zip :
	zip shingShang.zip main.c plateau.c plateau.h armee.c armee.h fonctions.c fonctions.h mouvement.c mouvement.h gestionTour.c gestionTour.h interface.c interface.h shingShang makefile

shingShang : plateau.o armee.o fonctions.o mouvement.o main.o interface.o gestionTour.o
	gcc -o shingShang plateau.o armee.o fonctions.o mouvement.o main.o interface.o gestionTour.o

plateau.o : plateau.c plateau.h
	gcc -c -Wall plateau.c

armee.o : armee.c armee.h
	gcc -c -Wall armee.c

fonctions.o : fonctions.c fonctions.h
	gcc -c -Wall fonctions.c

mouvement.o : mouvement.c mouvement.h
	gcc -c -Wall mouvement.c

main.o : main.c
	gcc -c -Wall main.c

interface.o : interface.c interface.h
	gcc -c -Wall interface.c
	
gestionTour.o : gestionTour.c gestionTour.h
	gcc -c -Wall gestionTour.c
