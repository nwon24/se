#ifndef _BUFFER_H
#define _BUFFER_H

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

void drawb(char *status_msg);
void set_status_msg(char *fmt, ...);

#endif
