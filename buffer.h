#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

struct buffer {
	char *s;
	int size;
};

struct buffer eb;

void bwrite(struct buffer *b, const char *s, int len);
void drawb(char *status_msg);
void freeb(struct buffer *b);
void status(struct buffer *b, const char *s, ... );
void row_to_buff(struct buffer *b);
void set_status_msg(char *s);
