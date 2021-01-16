#include "estruct.h"
#include "tty.h"
#include "file.h"

extern struct window win;

/* function intialises win struct defined
 * in "estruct.h"
 */

void init(char *name)
{
	win.cx = 0;
	win.cy = 0;
	win.fname = name;
	tty_dimensions(&win.nrow, &win.ncol); 
	win.rfile = 1;
	win.rowoff = 0;
	win.next_stat_msg = name;
	win.numrows = get_nrow(name);
	win.kill_buffer = NULL;
}
