CC = gcc
OPTION = -W -Wall -pedantic -std=c89 -O2 -g

main: main.o tableau.o cases.o vider_buffer.o mlv.o menu.o jeu_tmp.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` main.o tableau.o cases.o vider_buffer.o mlv.o menu.o jeu_tmp.o `pkg-config --libs-only-l MLV` -o main

main.o: main.c tableau.h cases.h vider_buffer.h mlv.h menu.h jeu.h
	$(CC) $(OPTION) main.c -c

tableau.o: tableau.c tableau.h
	$(CC) $(OPTION) tableau.c -c

cases.o: cases.c cases.h
	$(CC) $(OPTION) cases.c -c

vider_buffer.o: vider_buffer.c vider_buffer.h
	$(CC) $(OPTION) vider_buffer.c -c

mlv.o: mlv.c mlv.h
	$(CC) $(OPTION) mlv.c -c

menu.o: menu.c menu.h
	$(CC) $(OPTION) menu.c -c

jeu_tmp.o: jeu_tmp.c jeu.h
	$(CC) $(OPTION) jeu_tmp.c -c

clean:
	rm -rf *.o *~ *.d main