#include "mapa.h"
#include <raylib.h>

int map[MAP_ROWS][MAP_COLS] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 },
    { 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1 },
    { 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1 },
    { 1, 2, 1, 2, 1, 1, 1, 0, 1, 1, 1, 2, 1, 2, 1 },
    { 1, 2, 2, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 2, 1 },
    { 1, 1, 1, 2, 1, 0, 3, 3, 3, 0, 1, 2, 1, 1, 1 },
    { 0, 0, 1, 2, 2, 0, 3, 3, 3, 0, 2, 2, 1, 0, 0 },
    { 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1 },
    { 1, 2, 2, 2, 1, 0, 1, 1, 1, 0, 1, 2, 2, 2, 1 },
    { 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1 },
    { 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1 },
    { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

void DrawGameMap(void)
{
    int offsetX = 50;
    int offsetY = 50;

    for (int i = 0; i < MAP_ROWS; i++)
    {
        for (int j = 0; j < MAP_COLS; j++)
        {
            int posX = offsetX + j * TILE_SIZE;
            int posY = offsetY + i * TILE_SIZE;

            switch (map[i][j])
            {
                case TILE_WALL:
                    DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, (Color){0, 0, 100, 255});
                    DrawRectangleLinesEx((Rectangle){posX, posY, TILE_SIZE, TILE_SIZE}, 2, BLUE);
                    break;

                case TILE_COIN:
                    DrawCircle(posX + TILE_SIZE/2, posY + TILE_SIZE/2, TILE_SIZE/4, GOLD);
                    DrawCircleLines(posX + TILE_SIZE/2, posY + TILE_SIZE/2, TILE_SIZE/4, YELLOW);
                    break;

                default:
                    break;
            }
        }
    }
}