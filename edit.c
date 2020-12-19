/* edit.c
 * This file contains functions for removing
 * and adding text to row structs */

#include "edit.h"

/* The following function inserts a single
 * character into string s of a row struct at position pos
 */

void insert_char(struct row *erow, int pos, char c)
{
	/* First, we need to allocate enough memory */
	erow->s = realloc(erow->s, erow->size + 1);
	int i;
	
	/* Now we loop backwards over the string to shift
	 * everything forward to create a space for the new
	 * character
	 */
	
	for (i = erow->size; i >= pos; i--)
		erow->s[i] = erow->s[i - 1];
	erow->s[pos] = c;
	erow->size++;
	erow->s[erow->size] = '\0';
}

void del_char(struct row *erow, int pos, char c)
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
