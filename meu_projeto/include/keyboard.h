#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

void keyboardInit(void);
void keyboardClose(void);
int  keyboardRead(void); // retorna char (int) lido ou -1
int  keyboardKbhit(void);

#endif
