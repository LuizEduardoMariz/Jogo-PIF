#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

void keyboardInit(void);
void keyboardClose(void);
int  keyboardRead(void);
int  keyboardKbhit(void);

#endif
