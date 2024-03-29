#include "cursor.h" 
#include "buffer.h" 
 
extern struct window win; 
 
/* The functions in this file are pretty self-explanatory */ 
 
void forward_char(void) 
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
 
void backward_char(void) 
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
 
void down_line(void) 
{ 
	set_status_msg(win.fname); 
	if (win.cy == win.numrows - 1) { 
		; 
	} else if (win.cy < win.numrows && win.absolute_cy == win.nrow - 2) { 
		win.rowoff++; 
		win.cy++; 
	} else { 
		win.cy++; 
	} 
 
	if (win.cx > win.rows[win.cy].size) 
		win.cx = win.rows[win.cy].size; 
} 
 
void up_line(void) 
{ 
	set_status_msg(win.fname); 
	if (win.absolute_cy == 0 && win.rowoff > 0) { 
		win.rowoff--; 
		win.cy--; 
	} else if (win.cy == 0 && win.rowoff == 0) { 
		; 
	} else { 
		win.cy--; 
	} 
	/* Make sure cursor can only go to valid positions */ 
	if (win.cx > win.rows[win.cy].size) 
		win.cx = win.rows[win.cy].size; 
} 
 
void goto_sol(void) 
{ 
	set_status_msg(win.fname); 
	win.cx = 0; 
} 
 
void goto_eol(void) 
{ 
	set_status_msg(win.fname); 
	win.cx = win.rows[win.cy].size; 
} 
 
void goto_next_word(void) 
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
 
void goto_back_word(void) 
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
 
/* Same as above, just the opposite direction */ 
void goto_char_back(int c) 
{ 
	int old_cx = win.cx; 
	while (win.rows[win.cy].s[win.cx] != c && win.cx != 0) 
		win.cx--; 
 
	if (win.rows[win.cy].s[win.cx] != c) 
		win.cx = old_cx; 
} 
 
void goto_eof(void) 
{ 
	while (win.cy != win.numrows - 1) 
		down_line(); 
	goto_eol(); 
	while (win.numrows - win.rowoff >= win.nrow) 
		win.rowoff++; 
} 
 
void goto_sof(void) 
{ 
	while (win.cy != 0) 
		up_line(); 
	goto_sol(); 
	win.rowoff = 0; 
} 
 
void goto_line(int num) 
{ 
	if (num > win.numrows - 1 || num < 0) 
		return; 
	win.cy = num; 
	if (win.cy > win.nrow) 
		win.rowoff = win.rowoff + (win.cy % win.nrow); 
} 
