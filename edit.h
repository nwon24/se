#ifndef _EDIT_H
#define _EDIT_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "estruct.h"

#define TAB_SIZE 8
#define NO_TAB 0
#define BEG_TAB 1
#define END_TAB 2

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
int check_tab(struct row *erow, int pos);
void del_tab(void);
void goto_next_word(void);
void goto_back_word(void);
void copy_segment(struct row *erow, int start, int end);
void cut_segment(struct row *erow, int start, int end);
void put_segment(struct row *erow, int start);
void put_kill_buffer(void);
int count_next_word(void);
void cut_word(void);
void copy_word(void);

#endif
