/* main.c 
   A simple text editor written in C */ 
 
#include "estruct.h" 
#include "tty.h" 
#include "input.h" 
#include "buffer.h" 
#include "command.h" 
#include "file.h" 
 
extern struct window win; 
 
static void usage(void) 
{ 
	printf("se - A simple text editor\nUSAGE: se [FILE]\n"); 
	printf("If file does not exist, it will be created.\n"); 
	printf("Commands:\n\
	j, k, l, i: move cursor\n\
	e: change to edit mode\n\
	f: move cursor forward and change to edit mode\n\
	b: move cursor backward and change to edit mode\n\
	0, $: move cursor to start and end of line respectively\n\
	A, E: move cursor to start/end of line and change to edit mode\n\
	d, D: move forward/backward by one word\n\
	t, T: move forward/backward to specified char\n\
	1, !: move to start/end of file\n\
	L   : display line information\n\
	ESC: Switch back to command mode\n\
	In edit mode, basic Emacs-like keybindings work.\n"); 
	exit(1); 
} 
int main(int argc, char *argv[]) 
{ 
        /* For now, we say that the program must be invoked with 
         * the name of an existing file. UPDATE: program can now be invoked  
         * with a file name that doesn't exist and it will be created. 
         */ 
         
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
 
	/* If file is emtpy or it is a new file, we call the init_file function to give it a starting line */ 
	 
	if (!fexist(win.fname) || win.numrows == 0)
		init_file(); 

        /* This can NOT be an infinite loop - there is always some input that exits in either command or
           insert mode. The return at the end is never invoked, since the program is always exited from
           one of the two functions. */ 
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
