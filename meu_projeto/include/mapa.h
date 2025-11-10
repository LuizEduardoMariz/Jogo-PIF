#ifndef MAPA_H
#define MAPA_H

#define MAP_ROWS 14
#define MAP_COLS 15
#define TILE_SIZE 30

#define TILE_WALL 1
#define TILE_PATH 0
#define TILE_COIN 2

void DrawGameMap(void);
void UpdateCoins(void);
void InitCoinSound(void);
void UnloadCoinSound(void);
void CheckCoinCollision(int playerX, int playerY);

#endif