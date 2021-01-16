#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "estruct.h"

void insert_char(struct row *erow, int pos, char c);
void del_char(struct row *erow, int pos);
void write_to_disk(char *name);
void new_line(char *s, size_t len, int pos);
char *split_line(struct row *erow, int pos);
void del_line(int pos);
void append_line(char *s);
void cut_line(int pos);
void copy_line(int pos);
int put_line(int pos);
