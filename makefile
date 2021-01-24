CC=gcc
# In these flags, -fcommon has to be there becasue this project started with an older
# version of gcc, and it didn't like declaraing global variables in header files with 
# extern. Instead, extern had to be placed in the source files. When the latest compiler
# was used, the linker threw an error because gcc 10 defaults to -fno-common, so I just added
# -fcommon to the flags instead of rewriting everything.
CFLAGS=-std=c99 -Wall -pedantic -O1 -fcommon 
TARGET=se
OBJ=input.o main.o cursor.o buffer.o tty.o edit.o file.o init.o command.o

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)
%.o: %.c
	$(CC) $< -c $(CFLAGS) -o $@
clean:
	rm *.o se
