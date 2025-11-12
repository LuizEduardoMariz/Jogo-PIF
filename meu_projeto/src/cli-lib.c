#include "../include/cli-lib.h"
#include <sys/ioctl.h>
#include <fcntl.h>

static struct termios oldt, newt;

void cli_init() {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // desativa buffer 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    cli_hide_cursor();
}

void cli_close() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cli_show_cursor();
}

void cli_clear() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void cli_gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}


void cli_hide_cursor() {
    printf("\033[?25l");
    fflush(stdout);
}


void cli_show_cursor() {
    printf("\033[?25h");
    fflush(stdout);
}


int cli_kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int cli_getch() {
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
