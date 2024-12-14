CC = gcc
OPTION = -W -Wall -pedantic -std=c89 -O2

2048: main.o tableau.o cases.o mlv.o menu.o jeu.o score.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` main.o tableau.o cases.o mlv.o menu.o jeu.o score.o `pkg-config --libs-only-l MLV` -o 2048

main.o: main.c tableau.h cases.h mlv.h menu.h jeu.h score.h
	$(CC) $(OPTION) main.c -c

tableau.o: tableau.c tableau.h
	$(CC) $(OPTION) tableau.c -c

cases.o: cases.c cases.h
	$(CC) $(OPTION) cases.c -c

mlv.o: mlv.c mlv.h
	$(CC) $(OPTION) mlv.c -c

menu.o: menu.c menu.h
	$(CC) $(OPTION) menu.c -c

jeu.o: jeu.c jeu.h
	$(CC) $(OPTION) jeu.c -c

score.o: score.c score.h
	$(CC) $(OPTION) score.c -c

clean:
	rm -rf *.o *~ 2048