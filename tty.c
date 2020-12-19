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

	/* turn off flags to get into 'raw' mode */
	ntty.c_iflag &= ~(IGNBRK | BRKINT | IGNPAR | PARMRK | INPCK | INLCR | IGNCR | ICRNL | IXON);
	ntty.c_lflag &= ~(ISIG | ICANON | ECHO | IEXTEN);
	ntty.c_oflag &= ~(OPOST | ONLCR | OCRNL);

	ntty.c_cc[VMIN] = 1;
	ntty.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &ntty);
}

/* revert terminal settings so user has normal terminal
 * experience on program exit.
 */

void tty_revert(void)
{
	tcsetattr(0, TCSAFLUSH, &otty);
}

/* This function gets terminal dimensions in terms of
 * number of rows and number of columns. This should work
 * on most terminals. Uses ioctl. Arguments are passed by reference
 * so that struct members nrow and ncol can be modified directly
 */

void tty_dimensions(int *r, int *c)
{
	struct winsize w;
	ioctl(1, TIOCGWINSZ, &w);
	*r = w.ws_row;
	*c = w.ws_col;
}
