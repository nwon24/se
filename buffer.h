#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct buffer {
	char *s;
	int size;
};

struct buffer eb;

void bwrite(struct buffer *b, const char *s, int len);
void drawb();
void freeb(struct buffer *b);
void status(struct buffer *b, char *s);
void row_to_buff(struct buffer *b);
