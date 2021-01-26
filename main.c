/* main.c
   A simple text editor written in C */

#include "estruct.h"
#include "tty.h"
#include "input.h"
#include "buffer.h"
#include "command.h"
#include "file.h"

extern struct window win;

void usage()
{
	printf("se - A simple text editor\nUSAGE: se [FILE]\n");
	printf("If file does not exist, it will be created.\n");
	printf("Commands:\n \
	j, k, l, i: move cursor\n \
	e: change to edit mode\n \
	f: move cursor forward and change to edit mode\n \
	b: move cursor backward and change to edit mode\n \
	0, $: move cursor to start and end of line respectively\n \
	A, E: move cursor to start/end of line and change to edit mode\n \
	ESC: Switch back to command mode\n \
	In edit mode, basic Emacs-like keybindings work.\n");
	exit(1);
}
int main(int argc, char *argv[])
{
        /* For now, we say that the program must be invoked with
         * the name of an existing file */
        
	if (argc < 2) {
		printf("No file specified.\n");
		usage();
	}

	if (argc > 2) {
		printf("Too many arguments.\n");
		usage();
	}
	tty_raw();
	init(argv[1]);
	int exist = fexist(win.fname);

	/* If file is emtpy or it is a new file, we call the init_file function to give it a starting line */
	
	if (!exist || win.numrows == 0) {
		init_file();
	}
	goto loop;
loop:
	while (1) {
		/* Get terminal dimensions every time we enter
		 * loop, since user may have resized window, perhaps on a graphical terminal emulator */
		tty_dimensions(&win.nrow, &win.ncol);
		drawb(win.next_stat_msg);

		if (win.cur_mode == COMMAND_MODE)
			command_mode();
		else
			insert_mode();
	}
	return 0;
}
