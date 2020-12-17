/* file.c
   File I/O functions */
#include "file.h"
#include "estruct.h"
#include "buffer.h"

/* This function fetches one line from a file. It returns this line,
   not including the newline character. It assumes the file exists. */

extern struct window win;
extern struct buffer eb;

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
		line = realloc(line, sizeof(line) + 1);
	}		
		
	line = realloc(line, sizeof(line) + 1);
	line[i] = '\0';
	fclose(fp);
	return line;
}

int fexist(char *file)
{
	FILE *fp = fopen(file, "r");
	if (fp == NULL) {
		return 1;
	} else {
		fclose(fp);
		return 0;
	}
} 

int get_nrow(char *file)
{
	int exist = fexist(file);
	if (exist == 1)
		return 0;
	FILE *fp = fopen(file, "r");
	char c;
	int nrow;
	while ((c = getc(fp)) != EOF) {
		if (c == '\n')
			++nrow;
	}
	fclose(fp);
	return nrow;
}

void read_into_struct(char *file)
{
	win.numrows = get_nrow(file);
	int i = 0;
	while (i < win.numrows) {
		char *line = fgetline(file, i + 1);
		win.rows[i].s = line;
		win.rows[i].size = strlen(line);
		i++;
	}
}
