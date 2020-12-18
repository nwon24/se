/* input.c
   Handles user input and processes them */

#include "tty.h"
#include "input.h"
#include "estruct.h"

extern struct window win;

/* read a single key and return it */

int readk(void)
{
	int c;
	read(0, &c, 1);
	return c;
}

/* Process the key returned in the above
 * function. At the moment, there are only statements
 * to change cursor position. TODO: For some reason, program
 * does not seem to be reading key presses correctly, with 'q'
 * not invoking the program exit, even though it is stated
 * explicitly below.
 */

void process_key()
{
	int c = readk();
	
	switch (c) {
	case 'q':
		tty_revert();
		write(1, "\033[2J", 4);
		write(1, "\033[H", 3);
		exit(0);
		break;
                
        /* In the following change cursor position statements,
         * precautions are taken to stop cursor moving off screen
         * (i.e. win.cx and win.cy cannot be less than 0
         */
        
	case 'f':
		win.cx++;
		break;
	case 'd':
		if (win.cx == 0)
			break;
		win.cx--;
		break;
	case 'k':
		if (win.cy == 0)
			break;
		win.cy--;
		break;
	case 'j':
		win.cy++;
		break;
	default:
		/* Don't do anything for now */
		break;
	}
}
