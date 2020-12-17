CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -O1

edit: *.o
	$(CC) *.o -o edit $(CFLAGS)
*.o: *.c
	$(CC) *.c -c $(CFLAGS)
clean:
	rm *.o edit
