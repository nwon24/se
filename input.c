/* input.c
   Handles user input and processes them */

#include "tty.h"
#include "input.h"
#include "estruct.h"

extern struct window win;

int readk(void)
{
	int c;
	read(0, &c, 1);
	return c;
}

void process_key()
{
	int c = readk();
	
	switch (c) {
	case 'q':
/*		tty_revert();
		write(1, "\033[2J", 4);
		write(1, "\033[H", 3); */
		exit(0);
		break;
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
		write(1, "a", 1);
		break;
	}
}
