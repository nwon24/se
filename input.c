/* input.c
   Handles user input and processes them */

#include "tty.h"
#include "input.h"
#include "buffer.h"
#include "edit.h"

#ifndef TAB_SIZE
#define TAB_SIZE 8
#endif

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
		if (win.nsaved && win.status_mode != 1) {
			char *msg = "File has unsaved changes. Press CTRL-x again to quit.";
			set_status_msg(msg);
			win.status_mode = 1;
			break;
		} else {
			tty_revert();
			write(1, "\033[2J", 4);
			write(1, "\033[H", 3);
			exit(0);
			break;
		}
		
	/* In the following change cursor position statements,
	 * precautions are taken to stop cursor moving off screen
	 * (i.e. win.cx and win.cy cannot be less than 0
	 * Also, the final plan will be to implement both emacs-like
	 * and vim-like keybindings to move the cursor. (No arrow keys!)
	 */
	
	case CTRL('f'):

		/* The following if statement allows cursor to move to next line
		 * at end of current one. We also reset status message back to file name
		 * in case it has changed since last refresh
		 */
		set_status_msg(win.fname);
		if (win.cx == win.rows[win.cy].size && win.cy != win.numrows - 1) {
			win.cy++;
			win.cx = 0;
			break;
		} else if (win.cy == win.numrows - 1 && win.cx == win.rows[win.cy].size) {
			break;
		} else {
			win.cx++;
			break;
		}
	case CTRL('b'):
		set_status_msg(win.fname);
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
		set_status_msg(win.fname);
		if (win.absolute_cy == 0 && win.rowoff > 0) {
			win.rowoff--;
			win.cy--;
			break;
		} else if (win.cy == 0 && win.rowoff == 0) {
			break;
		} else {
			win.cy--;
			break;
		}
	case CTRL('n'):
		set_status_msg(win.fname);
		if (win.cy == win.numrows - 1) {
			break;
		} else if (win.cy < win.numrows && win.absolute_cy == win.nrow - 2) {
			win.rowoff++;
			win.cy++;
			break;
		} else if (win.rows[win.cy + 1].size < win.rows[win.cy].size && win.cy > win.rows[win.cy + 1].size) {
			win.cy++;
			win.cx = win.rows[win.cy].size;
			break;
		} else {
			win.cy++;
			break;
		}
	case CTRL('e'):
		set_status_msg(win.fname);
		win.cx = win.rows[win.cy].size;
		break;
	case CTRL('a'):
		win.cx = 0;
		set_status_msg(win.fname);
		break;
	case CTRL('d'):
	case 127:
		if (win.cx == 0 && win.cy == 0) {
			break;
		} else if (win.cx == 0 && win.cy != 0) {
			char *tmp = malloc(win.rows[win.cy].size);
			strcpy(tmp, win.rows[win.cy].s);
			del_line(win.cy);
			win.cy--;
			win.rows[win.cy].s = realloc(win.rows[win.cy].s, win.rows[win.cy].size + strlen(tmp));
			strcat(win.rows[win.cy].s, tmp);
			win.rows[win.cy].size += strlen(tmp);
			win.cx = win.rows[win.cy].size;
			break;
		} else {
			del_char(&win.rows[win.cy], win.cx - 1);
			win.cx--;
			break;
		}
		case CTRL('w'):
			write_to_disk(win.fname);
			set_status_msg(win.fname);
			break;
		case 13:
			set_status_msg(win.fname);
			if (win.cx == 0) {
				new_line(" ", 2, win.cy);
				win.cx = 0;
				win.cy++;
				win.nsaved = 1;
				break;
			} else if (win.cy == win.numrows - 1 && win.cx == win.rows[win.cy].size) {
				append_line(" ");
				win.cx = 0;
				win.cy++;
				win.nsaved = 1;
				break;
			} else if (win.cx == win.rows[win.cy].size) {
				new_line(" ", 2, win.cy + 1);
				win.cy++;
				win.cx = 0;
				win.nsaved = 1;
				break;
			} else if (win.cy != win.numrows - 1) {
				char *line = split_line(&win.rows[win.cy], win.cx);
				win.cy++;
				new_line(line, strlen(line), win.cy);
				win.cx = 0;
				win.nsaved = 1;
				break;
			} else {
				char *line = split_line(&win.rows[win.cy], win.cx);
				win.cy++;
				append_line(line);
				win.cx = 0;
				win.nsaved = 1;
				break;
			}	
		case '\0':
			break;
		
		/* The escape key. This can come about when pressing keys like the home
		 * keys as well, since they are sent as multi byte combinations. For now
		 * we do nothing if we receive a literal escape or any other key that begins with
		 * an escape.
		 */
		case 27:
			set_status_msg(win.fname);
			break;
		case '\t':
			insert_char(&win.rows[win.cy], win.cx, '\t');
			win.cx += TAB_SIZE - 1;
			break;

		/*  Next are the copy, cut and paste keys */
		case CTRL('c'):
			copy_line(win.cy);
			set_status_msg(win.fname);
			break;
		case CTRL('k'):
			set_status_msg(win.fname);
			cut_line(win.cy);
			if (win.nsaved != 1)
				win.nsaved = 1;
			break;
		/* Until I figure out what alt + key combination does to a key, (like the CTRL macro), 
		 * we will have to just use this key combination!
		 */
		case CTRL('y'):
			set_status_msg(win.fname);
			put_line(win.cy);
			if (win.nsaved != 1)
				win.nsaved = 1;
			break;
		default:
			/* Default is to insert char */
			insert_char(&win.rows[win.cy], win.cx, c);
			set_status_msg(win.fname);
			win.cx++;
			break;
		}
}
