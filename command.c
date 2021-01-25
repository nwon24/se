#include "input.h"
#include "buffer.h"
#include "cursor.h"
#include "command.h"
#include "edit.h"
#include "tty.h"

extern struct window win;

void command_mode()
{
	char c = readk();

	switch (c) {
	/* WARNING: The quit command here does not have protection against unsaved
           files yet */
	case 'q':
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

	default:
		break;
	}
}
