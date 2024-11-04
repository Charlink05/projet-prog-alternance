CC = gcc
OPTION = -W -Wall -pedantic -std=c89 -O2

main: main.o tableau.o cases.o 
	$(CC) $(OPTION) main.o tableau.o cases.o -o main

main.o: main.c
	$(CC) $(OPTION) main.c -c

tableau.o: tableau.c
	$(CC) $(OPTION) tableau.c -c

cases.o: cases.c
	$(CC) $(OPTION) cases.c -c

clean:
	rm -rf *.o *~ main