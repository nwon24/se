#ifndef _CURSOR_H  
#define _CURSOR_H  
  
#include "edit.h"  
  
void forward_char(void);  
void backward_char(void);  
void down_line(void);  
void up_line(void);  
void goto_eol(void); /* go to end of line */  
void goto_sol(void); /* go to start of line */  
void goto_char(int c);
void goto_char_back(int c); 
void goto_eof(void);  
void goto_sof(void);  
void goto_line(int num);  
  
#endif  
