#include "input.h"
#include "buffer.h"
#include "cursor.h"
#include "command.h"
#include "tty.h"
#include <ctype.h>

extern struct window win;

void command_mode()
{
	char c = readk();
	char *split;
	switch (c) {
	/* WARNING: The quit command here does not have protection against unsaved
           files yet */
	case 'q':
		if (win.nsaved && !win.quit_confirm) {
			char *s = "File has unsaved changes, press q again to quit";
			set_status_msg(s);	
			win.quit_confirm = 1;
			break;
		}
		write(1, "\033[2J", 4);
		write(1, "\033[H", 3);
		tty_revert();
		exit(0);

	case 'j':
		backward_char();
		break;

	case 'k':
		down_line();
		break;

	case 'l':
		forward_char();
		break;

	case 'i':
		up_line();
		break;

	case '$':
		goto_eol();
		break;

	case '0':
		goto_sol();
		break;

	case 'w':
		write_to_disk(win.fname);
		break;

	/* e for edit */
	case 'e':
		win.cur_mode = INSERT_MODE;
		break;

	/* n for new line */
	case 'n':
		new_line(" ", 2, win.cy + 1);
		win.cur_mode = INSERT_MODE;
		win.cx = 0;
		win.cy++;
		win.nsaved = 1;
		break;

	case 'N':
		new_line(" ", 2, win.cy);
		win.cur_mode = INSERT_MODE;
		win.cx = 0;
		win.nsaved = 1;
		break;

	/* These commands move the cursor backwards/forwards and
	   put the user into insert mode */
	case 'f':
		forward_char();
		win.cur_mode = INSERT_MODE;
		break;

	case 'b':
		backward_char();
		win.cur_mode = INSERT_MODE;
		break;

	case 'E':
		goto_eol();
		win.cur_mode = INSERT_MODE;
		break;

	case 'A':
		goto_sol();
		win.cur_mode = INSERT_MODE;
		break;

	case 'd':
		goto_next_word();
		break;

	case 'D':
		goto_back_word();
		break;

	case 't':
		goto_specified_char();
		break;

	case 'T':
		goto_specified_char_backwards();
		break;

	case 'c':
		copy_command();
		break;

	case 'y':
		cut_command();
		break;

	case 'p':
		put_kill_buffer();
		break;

	case 's':
		if (win.cx == 0 || win.cx == win.rows[win.cy].size)
			break;
		split = split_line(&win.rows[win.cy], win.cx);
		new_line(split, strlen(split), win.cy + 1);
		win.cur_mode = INSERT_MODE;
		win.cy++;
		win.cx = 0;
		break;
	case '1':
		goto_sof();
		break;
	
	case '!':
		goto_eof();
<<<<<<< HEAD
		break;
=======
		break;		

	case '\n':
		down_line();
		win.cx = 0;
		break;

>>>>>>> d7f62a37fdd582547ea5bafc968a839be17d0fed
	default:
		break;
	}
}

/* Here are some sub routines to be invoked within other commands */
void goto_specified_char()
{
	char c = readk();
	if (c == 27)
		return;
	goto_char(c);
}

void goto_specified_char_backwards()
{
	char c = readk();
	if (c == 27)
		return;
	goto_char_back(c);
}

void copy_command()
{
	char c = readk();
	if ((isdigit(c)) > 0) {
		copy_segment(&win.rows[win.cy], win.cx, win.cx + (c - '0'));
		return;
	}
	if (c == 'c')
		copy_line(win.cy);
	else if ( c== 'w')
		copy_word();
	else
		return;
}

void cut_command()
{
	char c = readk();
	if ((isdigit(c)) > 0) {
		cut_segment(&win.rows[win.cy], win.cx, win.cx + (c - '0'));
		return;
	}
	if (c == 'y')
		cut_line(win.cy);
	else if (c == 'w')
		cut_word();
	else
		return;
}