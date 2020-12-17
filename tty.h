#include <termios.h>
#include <sys/ioctl.h>

void tty_raw(void);
void tty_revert(void);
void tty_dimensions(int *r, int *c);
