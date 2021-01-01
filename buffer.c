/* buffer.c
   Functions for displaying, redrawing and updating buffer */

#include "buffer.h"
#include "estruct.h"
#include "file.h"

extern struct window win;
extern struct buffer eb;

/* Write to the buffer. The function is similar to the system call
   write(). It appends specified string to b->s, which is the string containting
   the contents of the buffer, before updating the size as well */
   
void bwrite(struct buffer *b, const char *s, int len)
{
	char *n = realloc(b->s, b->size + len);
	if (n == NULL) return;
	memcpy(&n[b->size], s, len);
	b->s = n;
	b->size += len;
}

/* Draws buffer. It first draws the tildes on the side, and then the status bar, before
   actually displaying the text displayed in the array of row structs. TODO: There is an odd
   flickering affect each time the screen is re-drawn. */
   
void drawb()
{
	eb.s = NULL;
	eb.size = 0;
	bwrite(&eb, "\033[?25l", 6);
	bwrite(&eb, "\033[H", 3);
	for (int i = 0; i < win.ncol; i++) {
		bwrite(&eb, "~", 1);
		bwrite(&eb, "\033[K", 3);
		bwrite(&eb, "\r\n", 2);
	}

	if (win.nsaved == 1)
		status(&eb, "%s*", win.fname);
	else
		status(&eb, "%s", win.fname);
	bwrite(&eb, "\033[H", 3);
	/* check if we should be reading from the file */
	if (win.rfile == 1) {
		read_into_struct(win.fname);
		win.rfile = 0;
	}
	row_to_buff(&eb);
	char buf[32];
	snprintf(buf, sizeof(buf), "\033[%d;%dH", win.cy + 1, win.cx + 1);
	bwrite(&eb, buf, strlen(buf)); 	
	bwrite(&eb, "\033[?25h", 6); 
	write(1, eb.s, eb.size);
	freeb(&eb); 
}

void freeb(struct buffer *b)
{
	free(b->s);
}

/* status bar in inverted colours */
	
void status(struct buffer *b, const char *s, ... )
{
	va_list args;
	va_start(args, s);
	bwrite(b, "\033[7m", 4);
	char status[80];
	int len = vsnprintf(status, sizeof(status), s, args);
	if (len > win.ncol) len = win.nrow;
	bwrite(b, status, len); 
	while (len < win.ncol) {
		bwrite(b, " ", 1);
		len++;
	}
	bwrite(b, "\033[m", 3);
}

/* This function appends all the strings in the array
   of structs to the buffer, to be written onto the screen.
   TODO: At the moment, it only writes the first line, since
   the get_nrows() function is faulty and incorrectly reports
   the number of lines as 0 */
   
void row_to_buff(struct buffer *b)
{
	int i;
	for (i = 0; i <= win.numrows - 1; i++) {
		bwrite(b, win.rows[i].s, win.rows[i].size);
		bwrite(b, "\r\n", 2);
	}
}
