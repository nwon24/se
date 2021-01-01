/* input.c
   Handles user input and processes them */

#include "tty.h"
#include "input.h"
#include "edit.h"

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
         * and vim-like keybindings to move the cursor. (No arrow keys!)
         */
        
        case CTRL('f'):

		/* The following if statement allows cursor to move to next line
		 * at end of current one
		 */

		if (win.cx == win.rows[win.cy].size && win.cy != win.numrows) {
			win.cy++;
			win.cx = 0;
			break;
		} else if (win.cy == win.numrows) {
			break;
		}
		win.cx++;
		break;
        case CTRL('b'):
		if (win.cx == 0 && win.cy != 0) {
			win.cy--;
			win.cx = win.rows[win.cy].size;
			break;
		} else if (win.cy == 0 && win.cx == 0) {
			break;
		}
		win.cx--;
		break;
        case CTRL('p'):
		if (win.cy == 0)
			break;
		win.cy--;
		break;
        case CTRL('n'):
		if (win.cy == win.numrows - 1)
			break;
		win.cy++;
		break;
	case CTRL('d'):
	case 127:
		del_char(&win.rows[win.cy], win.cx - 1);
		win.cx--;
		break;
	case CTRL('w'):
		write_to_disk(win.fname);
		break;
	case 13:
		if (win.cx == 0) {
			new_line(" ", 2, win.cy);
			win.cx = 0;
			win.cy++;
			break;
		} else {
			char *line = split_line(&win.rows[win.cy], win.cx);
			new_line(line, sizeof(line), win.cy);
			win.cx = 0;
			win.cy++;
			break;
		}

	case '\0':
		break;
	default:
		/* Default is to insert char */
		insert_char(&win.rows[win.cy], win.cx, c);
		win.cx++;
		break;
	}
}
