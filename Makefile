CC = gcc
OPTION = -W -Wall -pedantic -std=c89 -O2

main: main.o tableau.o cases.o vider_buffer.o mlv.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs_only_other --libs_only_L MLV` main.o tableau.o cases.o vider_buffer.o mlv.o `pkg-config --libs-only-l MLV` -o main

main.o: main.c tableau.h cases.h vider_buffer.h
	$(CC) $(OPTION) main.c -c

tableau.o: tableau.c tableau.h
	$(CC) $(OPTION) tableau.c -c

cases.o: cases.c cases.h
	$(CC) $(OPTION) cases.c -c

vider_buffer.o: vider_buffer.c vider_buffer.h
	$(CC) $(OPTION) vider_buffer.c -c

mlv.o: mlv.c mlv.h
	$(CC) $(OPTION) mlv.c -c

clean:
	rm -rf *.o *~ *.d main