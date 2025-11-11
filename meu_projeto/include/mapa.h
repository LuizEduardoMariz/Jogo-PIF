#ifndef MAPA_H
#define MAPA_H

#include "screen.h"

#define MAP_ROWS 14
#define MAP_COLS 15
#define TILE_SIZE 30

#define TILE_WALL 1
#define TILE_PATH 0
#define TILE_COIN 2

void DrawGameMapASCII(Player *player, Monstro *monstros, int numMonstros);
void CheckCoinCollision(int playerX, int playerY);

#endif
