/* edit.c
 * This file contains functions for removing
 * and adding text to row structs */

#include "edit.h"

extern struct window win;

/* The following function inserts a single
 * character into string s of a row struct at position pos
 */

void insert_char(struct row *erow, int pos, char c)
{
	/* First, we need to allocate enough memory 
	   Instead of just calling realloc(), we copy
	   the string into a temp variable and the use
	   malloc instead. Using realloc can lead to 
	   invalid pointer errors once we initialise new
	   rows */
	char *tmp = malloc(erow->size);
	strcpy(tmp, erow->s);
	erow->s = malloc(erow->size + 2);
	strcpy(erow->s, tmp);
	int i;
	
	/* Now we loop backwards over the string to shift
	 * everything forward to create a space for the new
	 * character
	 */
	
	for (i = erow->size; i > pos; i--)
		erow->s[i] = erow->s[i - 1];
	erow->s[pos] = c;
	erow->size++;
	erow->s[erow->size] = '\0'; /* reinsert terminating char */
	win.nsaved = 1;
}

void del_char(struct row *erow, int pos)
{
	int i;
	
	/* iterate over the array from pos
	 * and shift everything to the left
	 */
	
	for (i = pos; i <= erow->size; i++)
		erow->s[i] = erow->s[i + 1];
	erow->size--;
	erow->s[erow->size] = '\0';
	
	/* Now we deallocate some memory that the now
	 * deleted char occuped before
	 */
	
	erow->s = realloc(erow->s, erow->size);
	win.nsaved = 1;
}

/* This function writes the contents of the array
   of row structs into a file. If the file name parameter specified
   is the original file name, then the file is simply being saved. If it
   is a different name, then the file is being saved with a new name (equivalent
   of a save as) */
   
void write_to_disk(char *name)
{
	FILE *fp = fopen(name, "w");
	/* We need no error checking here because opening it with write mode
	   creates the file if it is not there */
	   
	int i;
	
	/* Now we loop over the array of row structs and write each of them into
	   the file, adding a newline character after each one. */
	   
	for (i = 0; i <= win.numrows - 1; i++) {
		fputs( win.rows[i].s, fp);
		fputs("\n", fp);
	}
	fclose(fp);
	win.nsaved = 0;
}

void new_line(char *s, size_t len, int pos)
{
	win.rows = realloc(win.rows, sizeof(struct row) * (win.numrows + 1));
	
	/* To insert a row struct in the array, we do a similar thing to the
	   insert char above: we loop over the array, shifitng everything from
	   position pos up, freeing a position for the new row struct. The procedure
	   is slightly more complicated becasue we have to reallocate memory and copy
	   the strings over. */

	int i;
	for (i = win.numrows; i > pos; i--) {
		win.rows[i].s = realloc(win.rows[i].s, win.rows[i - 1].size);
		memcpy(&win.rows[i].s, &win.rows[i - 1].s, win.rows[i - 1].size);
		win.rows[i].size = win.rows[i - 1].size;
	}
	win.rows[pos].s = realloc(win.rows[pos].s, len);
	win.rows[pos].s = s;
	win.rows[pos].size = len;
	win.numrows++;
} 

/* This function will split a row into two,
   which we use to handle the enter key when the 
   cursor is in the middle of a line. */
   
char *split_line(struct row *erow, int pos)
{
	/* Allocate enough memory for the split string */
	char *split = malloc(erow->size - pos + 1);

	/* copy over the characters from pos to end */
	int a = 0; /* just a counter */
	for (int i = pos; i < erow->size; i++) {
		split[a] = erow->s[i];
		a++;
	}

	/* update members of now split row */
	erow->s = realloc(erow->s, pos);
	erow->size = pos;
	erow->s[pos] = '\0';
	split[a] = '\0';
	return split;
}

/* The following function deletes a line at a given position */
void del_line(int pos)
{
	int i;
	for (i = pos; i < win.numrows - 1; i++) {
		win.rows[i].s = realloc(win.rows[i].s, win.rows[i + 1].size);
		win.rows[i].s = win.rows[i + 1].s;
		win.rows[i].size = win.rows[i + 1].size;
	}

	win.rows = realloc(win.rows, sizeof(struct row) * (win.numrows - 1));
	win.numrows--;
}

/* This function appends a new line to the array or row structs. We use a different
   function to the new line function above as it is easier to implement and debug if
   there are issues like seg faults */

void append_line(char *s)
{
	/* First, we allocate more memory */
	win.rows = realloc(win.rows, sizeof(struct row) * (win.numrows + 1));

	/* Then we simply set the new row's properties accordingly and update
           the numrows counter */

	win.rows[win.numrows].s = s;
	win.rows[win.numrows].size = strlen(s);
	win.numrows++;
}
