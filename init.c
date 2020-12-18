#include "estruct.h"
#include "tty.h"
#include "file.h"

extern struct window win;

void init(char *name)
{
	win.cx = 0;
	win.cy = 0;
	win.fname = name;
	tty_dimensions(&win.nrow, &win.ncol); 
	win.numrows = 0;
}
