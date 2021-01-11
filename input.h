#include <unistd.h>
#include <stdlib.h>

/* Following macros bitwise ANDs a character with 0x1f
 * which is what happens when you hold down the control
 * key with another character. This allows us to define
 * and map C-* like key bindings to different editor functions
 */

#ifndef CTRL
#define CTRL(key) ((key) & 0x1f)
#endif

char readk(void);
void process_key(void);
char status_input(void);
void nsaved_message(void);
