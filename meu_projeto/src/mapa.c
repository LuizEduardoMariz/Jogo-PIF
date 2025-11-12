#include "mapa.h"
#include "personagem.h"
#include "screen.h"
#include "raylib.h"

static int map[MAP_ROWS][MAP_COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
    {1,2,1,1,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,1,2,2,2,2,2,2,2,2,2,1,2,1},
    {1,2,1,2,1,1,1,0,1,1,1,2,1,2,1},
    {1,2,2,2,1,0,0,0,0,0,1,2,2,2,1},
    {1,1,1,2,1,0,0,0,0,0,1,2,1,1,1},
    {0,0,1,2,2,0,0,0,0,0,2,2,1,0,0},
    {1,1,1,2,1,0,0,0,0,0,1,2,1,1,1},
    {1,2,2,2,1,0,1,1,1,0,1,2,2,2,1},
    {1,2,1,2,2,2,2,2,2,2,2,2,1,2,1},
    {1,2,1,1,1,2,1,1,1,2,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void InitMap(Mapa *m) {
    m->linhas = MAP_ROWS;
    m->colunas = MAP_COLS;
    for (int i = 0; i < MAP_ROWS; i++)
        for (int j = 0; j < MAP_COLS; j++)
            m->tiles[i][j] = map[i][j];
}

void DrawMap(const Mapa *m) {
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            int tile = m->tiles[i][j];
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;
            if (tile == TILE_WALL)
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, DARKBROWN);
            else if (tile == TILE_COIN)
                DrawCircle(x + TILE_SIZE / 2, y + TILE_SIZE / 2, TILE_SIZE / 6, GOLD);
            else
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, DARKGRAY);
        }
    }
}

bool IsWall(const Mapa *m, int x, int y) {
    if (y < 0 || y >= m->linhas || x < 0 || x >= m->colunas) return true;
    return m->tiles[y][x] == TILE_WALL;
}

bool IsCoin(const Mapa *m, int x, int y) {
    if (y < 0 || y >= m->linhas || x < 0 || x >= m->colunas) return false;
    return m->tiles[y][x] == TILE_COIN;
}

void CollectCoin(Mapa *m, int x, int y) {
    if (y >= 0 && y < m->linhas && x >= 0 && x < m->colunas)
        if (m->tiles[y][x] == TILE_COIN)
            m->tiles[y][x] = TILE_PATH;
}

void ResetCoins(Mapa *m) {
    for (int i = 0; i < m->linhas; i++)
        for (int j = 0; j < m->colunas; j++)
            if (map[i][j] == TILE_COIN)
                m->tiles[i][j] = TILE_COIN;
}
