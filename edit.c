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
	/* First, we need to allocate enough memory */
	erow->s = realloc(erow->s, erow->size + 2);
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
}
