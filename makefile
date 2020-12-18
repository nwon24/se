CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -O1
TARGET=se

$(TARGET): *.o
	$(CC) *.o -o $(TARGET) $(CFLAGS)
*.o: *.c
	$(CC) *.c -c $(CFLAGS)
clean:
	rm *.o se
