#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct stat fs;

int fexist(char *file);
int get_nrow(char *file);
void read_into_struct(char *file);
void init_file(void);

#endif
