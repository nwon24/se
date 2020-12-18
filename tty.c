/* tty.c
   File contains functins for opening terminal,
   changing terminal settings (for raw mode), and closing
   it once we are done */

#include "tty.h"

static struct termios otty; /* old tty settings */
static struct termios ntty; /* new tty settings */

void tty_raw(void)
{
	tcgetattr(0, &otty);
	ntty = otty; /* initialise ntty so we can change its flags */

	ntty.c_iflag &= ~(IGNBRK | BRKINT | IGNPAR | PARMRK | INPCK | INLCR | IGNCR | ICRNL | IXON);
	ntty.c_lflag &= ~(ISIG | ICANON | ECHO | IEXTEN);
	ntty.c_oflag &= ~(OPOST | ONLCR | OCRNL);

	ntty.c_cc[VMIN] = 1;
	ntty.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &ntty);
}

void tty_revert(void)
{
	tcsetattr(0, TCSAFLUSH, &otty);
}

void tty_dimensions(int *r, int *c)
{
	struct winsize w;
	ioctl(1, TIOCGWINSZ, &w);
	*r = w.ws_row;
	*c = w.ws_col;
}
