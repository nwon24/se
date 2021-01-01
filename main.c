/* main.c
   A simple text editor written in C */

#include "estruct.h"
#include "tty.h"
#include "input.h"
#include "buffer.h"
#include "file.h"

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
	int exist = fexist(win.fname);
	if (exist == 1) {
		init_file();
	}
	goto loop;
loop:
	while (1) {
		/* Get terminal dimensions every time we enter
		 * loop, since user may have resized window */
		tty_dimensions(&win.nrow, &win.ncol);
		drawb();
		process_key();
	}
	return 0;
}
