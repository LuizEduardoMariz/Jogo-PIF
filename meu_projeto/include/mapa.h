#ifndef MAPA_H
#define MAPA_H

#include <stdbool.h>
#include "raylib.h"
#include "screen.h"

#define MAP_ROWS 14
#define MAP_COLS 15
#define TILE_SIZE 30

#define TILE_WALL 1
#define TILE_PATH 0
#define TILE_COIN 2

typedef struct {
    int linhas, colunas;
    int tiles[MAP_ROWS][MAP_COLS];
} Mapa;

void InitMap(Mapa *m);
void DrawMap(const Mapa *m);
bool IsWall(const Mapa *m, int x, int y);
bool IsCoin(const Mapa *m, int x, int y);
void CollectCoin(Mapa *m, int x, int y);
void ResetCoins(Mapa *m);

#endif
