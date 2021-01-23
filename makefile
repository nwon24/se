CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -O1 -fcommon
TARGET=se
OBJ=input.o main.o cursor.o buffer.o tty.o edit.o file.o init.o

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)
%.o: %.c
	$(CC) $< -c $(CFLAGS) -o $@
clean:
	rm *.o se
