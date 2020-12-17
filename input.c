/* input.c
   Handles user input and processes them */

#include "tty.h"
#include "input.h"

int readk(void)
{
	int c;
	read(0, &c, 1);
	return c;
}

void process_key(void)
{
	int c = readk();

	switch (c) {
	case 'x':
		tty_revert();
		write(1, "\033[2J", 4);
		exit(0);
	}
}
