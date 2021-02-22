#ifndef _COMMAND_H
#define _COMMAND_H

/* command_mode similar to vim
   Users are given the choice; they can stay in insert mode and
   stay modless or switch between modes to avoid getting hand injuries
   from Emacs-like key bindings */

void command_mode();
void goto_specified_char();
void goto_specified_char_backwards();
void cut_command();
void copy_command();
void display_line_status();
void goto_line_command();

#endif
