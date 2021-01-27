#include "cursor.h"
#include "buffer.h"

extern struct window win;

/* The functions in this file are pretty self-explanatory */

void forward_char()
{
	set_status_msg(win.fname);
	int i = check_tab(&win.rows[win.cy], win.cx);
	if (i == BEG_TAB) {
		win.cx += TAB_SIZE;
		return;
	}

	if (win.cx == win.rows[win.cy].size && win.cy != win.numrows - 1) {
		win.cy++;
		win.cx = 0;
	} else if (win.cy == win.numrows - 1 && win.cx == win.rows[win.cy].size) {
		return;
	} else {
		win.cx++;
	}
}

void backward_char()
{
	set_status_msg(win.fname);
	int i = check_tab(&win.rows[win.cy], win.cx);
	if (i == END_TAB) {
		win.cx -= TAB_SIZE;
		return;
	}
	if (win.cx == 0 && win.cy != 0) {
		win.cy--;
		win.cx = win.rows[win.cy].size;
		return;
	} else if (win.cy == 0 && win.cx == 0) {
		return;
	}
	win.cx--;
}

void down_line()
{
	set_status_msg(win.fname);
	if (win.cy == win.numrows - 1) {
		return;	
	} else if (win.cy < win.numrows && win.absolute_cy == win.nrow - 2) {
		win.rowoff++;
		win.cy++;
		return;
	} else if (win.rows[win.cy + 1].size < win.rows[win.cy].size && win.cy > win.rows[win.cy + 1].size) {
		win.cy++;
		win.cx = win.rows[win.cy].size;
		return;
	} else {
		win.cy++;
		return;
	}
}

void up_line()
{
	set_status_msg(win.fname);
	if (win.absolute_cy == 0 && win.rowoff > 0) {
		win.rowoff--;
		win.cy--;
		return;
	} else if (win.cy == 0 && win.rowoff == 0) {
		return;
	} else {
		win.cy--;
		return;
	}
}

void goto_sol()
{
	set_status_msg(win.fname);
	win.cx = 0;
}

void goto_eol()
{
	set_status_msg(win.fname);
	win.cx = win.rows[win.cy].size;
}

void goto_next_word()
{
	set_status_msg(win.fname);
	int old_cx = win.cx;
	while (win.rows[win.cy].s[win.cx] != ' ') {
		if (win.cx == win.rows[win.cy].size) {
			win.cx = old_cx;
			return;
		}
		win.cx++;
	}
	win.cx++;
}

void goto_back_word()
{
	set_status_msg(win.fname);
	int old_cx = win.cx;
	while (win.rows[win.cy].s[win.cx] != ' ') {
		if (win.cx == 0) {
			win.cx = old_cx;
			return;
		}
		win.cx--;
	}
	win.cx--;
}

/* This function moves the cursor to the next instance of char c in the current line */
void goto_char(int c)
{
	int old_cx = win.cx;
	while (win.rows[win.cy].s[win.cx] != c && win.cx < win.rows[win.cy].size)
		win.cx++;

	/* Return to old position if character not found in line */
	if (win.rows[win.cy].s[win.cx] != c)
		win.cx = old_cx;
}
