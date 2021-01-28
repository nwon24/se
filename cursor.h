#ifndef _CURSOR_H
#define _CURSOR_H

#include "edit.h"

void forward_char();
void backward_char();
void down_line();
void up_line();
void goto_eol(); /* go to end of line */
void goto_sol(); /* go to start of line */
void goto_char();
void goto_char_back();

#endif
