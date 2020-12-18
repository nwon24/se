/* input.c
   Handles user input and processes them */

#include "tty.h"
#include "input.h"
#include "estruct.h"

extern struct window win;

/* read a single key and return it 
 * Later this will be expanded to 
 * handle different keys that are handled
 * as escape sequences
 */

char readk(void)
{
	char c;
	read(0, &c, 1);
	return c;
}

/* Process the key returned in the above
 * function. At the moment, there are only statements
 * to change cursor position. 
 */

void process_key(void)
{
	char c = readk();
	
	switch (c) {
	case CTRL('x'):
		tty_revert();
		write(1, "\033[2J", 4);
		write(1, "\033[H", 3);
		exit(0);
		break;
                
        /* In the following change cursor position statements,
         * precautions are taken to stop cursor moving off screen
         * (i.e. win.cx and win.cy cannot be less than 0
         * Also, the final plan will be to implement both emacs-like
         * and vim-like keybindings to move the cursor.
         */
        
        case CTRL('f'):
	case 'f':
		win.cx++;
		break;
        case CTRL('b'):
	case 'd':
		if (win.cx == 0)
			break;
		win.cx--;
		break;
        case CTRL('p'):
	case 'k':
		if (win.cy == 0)
			break;
		win.cy--;
		break;
        case CTRL('n'):
	case 'j':
		win.cy++;
		break;
	default:
		/* Don't do anything for now */
		break;
	}
}
