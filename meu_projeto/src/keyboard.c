#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

static struct termios oldt, newt;

void keyboardInit(void) {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void keyboardClose(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

char keyboardRead(void) {
    char ch = 0;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

bool keyboardIsPressed(char key) {
    char c = keyboardRead();
    return (c == key);
}
