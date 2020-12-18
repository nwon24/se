/* main.c
   A simple text editor written in C */

#include "estruct.h"
#include "tty.h"
#include "input.h"
#include "buffer.h"

extern struct window win;

int main(int argc, char *argv[])
{
        /* For now, we say that the program must be invoked with
         * the name of an existing file */
        
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
	while (1) {
		drawb();
		process_key();
	}
	tty_revert();
	write(1, "\033[2J", 4);
	write(1, "\033[H", 3);
	return 0;
}
