/* main.c
   A simple text editor */

#include "estruct.h"
#include "tty.h"
#include "input.h"
#include "buffer.h"

extern struct window win;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("No file specified.\n");
		exit(1);
	}

	if (argc > 2) {
		printf("Too many arguments.\n");
		exit(1);
	}
	tty_raw();
	init(argv[1]);
	drawb();	
	process_key();
	tty_revert();
	write(1, "\033[2J", 4);
	write(1, "\033[H", 3);
	return 0;
}
