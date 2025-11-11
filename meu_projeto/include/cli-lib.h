#ifndef __CLI_LIB_H__
#define __CLI_LIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // para usleep
#include <termios.h>  // para controle do modo de terminal
#include <stdbool.h>

void cli_init();
void cli_close();
void cli_clear();
void cli_gotoxy(int x, int y);
void cli_hide_cursor();
void cli_show_cursor();
int  cli_kbhit();
int  cli_getch();

#endif
