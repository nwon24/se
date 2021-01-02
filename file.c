/* file.c
   File I/O functions */
#include "file.h"
#include "estruct.h"
#include "buffer.h"

/* This function fetches one line from a file. It returns this line,
   not including the newline character. It assumes the file exists. */

extern struct window win;
extern struct buffer eb;
extern struct stat fs;

char *fgetline(char *file, int pos)
{
	FILE *fp = fopen(file, "r");
	char *line = (char *)malloc(sizeof(char));
	char c;
	int i = 0;
	int nline = 0;
	while (nline != pos - 1) {
		c = getc(fp);
		if (c == '\n')
			++nline;
	}
	while ((c = getc(fp)) != '\n') {
		line[i] = c;
		++i;
		line = realloc(line, i + 1);
	}		
		
	line = realloc(line, i + 1);
	line[i] = '\0';
	fclose(fp);
	return line;
}

/* The following function checks if a file exists and returns
   exit success if it does */
   
int fexist(char *file)
{
	int exist = stat(file, &fs);
	if (exist == 0)
		return 0;
	else
		return 1;
}

/* TODO: fix bug here. For some reason, calling this function does not
   get correct number of rows in file. */
   
int get_nrow(char *file)
{
	FILE *fp = fopen(file, "r");
	int c;
	int nrows = 0;
	while ((c = getc(fp)) != EOF) {
		if (c == '\n')
			++nrows;;
	}
	fclose(fp);
	return nrows;
}

/* This function gets each line from the specified file and reads it into 
   the array of structs in the struct win. Enough space is first allocated.
   Bug here is related to above; since above function return number of rows as 0
   this function only reads one line into file, so not all the file is displayed. */
   
void read_into_struct(char *file)
{
	win.numrows = get_nrow(file);
	win.rows = malloc(sizeof(struct row) * win.numrows);
	int i = 0;
	while (i <= (win.numrows - 1)) {
		char *line = fgetline(file, i + 1);
		win.rows[i].s = malloc(sizeof(line));
		win.rows[i].s = line;
		win.rows[i].size = strlen(line);
		i++;
	}
	win.rfile = 0;
}

/* The following file initialises a new file
  It is used if user calls program with file that
 does not exist yet */

void init_file()
{
	win.numrows = 1;
	win.rows = malloc(sizeof(struct row));
	win.rows[0].s = " ";
	win.rows[0].size = 1;
	win.nfile = 1;
}
