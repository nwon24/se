#include <unistd.h>
#include <stdlib.h>

#ifndef CTRL
#define CTRL(key) ((key) & 0x1f)
#endif

char readk(void);
void process_key(void);
