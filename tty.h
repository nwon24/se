#ifndef _TTY_H
#define _TTY_H

#include <termios.h>
#include <sys/ioctl.h>

void tty_raw(void);
void tty_revert(void);
void tty_dimensions(int *r, int *c);

#endif
