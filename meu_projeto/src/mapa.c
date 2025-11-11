#include "../include/mapa.h"
#include "cli-lib.h"
#include <stdio.h>
#include <math.h>

static int map[MAP_ROWS][MAP_COLS] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 },
    { 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1 },
    { 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1 },
    { 1, 2, 1, 2, 1, 1, 1, 0, 1, 1, 1, 2, 1, 2, 1 },
    { 1, 2, 2, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 2, 1 },
    { 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1 },
    { 0, 0, 1, 2, 2, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0 },
    { 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1 },
    { 1, 2, 2, 2, 1, 0, 1, 1, 1, 0, 1, 2, 2, 2, 1 },
    { 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1 },
    { 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1 },
    { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

void DrawGameMapASCII(Player *player, Monstro *monstros, int numMonstros)
{
    screenGotoxy(0, 0);
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            int desenhou = 0;

            if ((int)(player->y) == i && (int)(player->x) == j) {
                printf("P");
                desenhou = 1;
            } else {
                for (int m = 0; m < numMonstros; m++) {
                    if (monstros[m].ativo && (int)(monstros[m].y) == i && (int)(monstros[m].x) == j) {
                        printf("M");
                        desenhou = 1;
                        break;
                    }
                }
            }

            if (!desenhou) {
                switch (map[i][j]) {
                    case 1: printf("#"); break;
                    case 2: printf("o"); break;
                    case 0: printf(" "); break;
                    default: printf(" "); break;
                }
            }
        }
        printf("\n");
    }
}

void CheckCoinCollision(int playerX, int playerY)
{
    if (playerY >= 0 && playerY < MAP_ROWS && playerX >= 0 && playerX < MAP_COLS) {
        if (map[playerY][playerX] == 2) {
            map[playerY][playerX] = 0;
        }
    }
}
    