#include "../include/mapa.h"
#include <raylib.h>
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

static float animTime = 0.0f;
static Sound coinSound;

void InitCoinSound(void)
{
    InitAudioDevice();
    coinSound = LoadSound("assets/sounds/coin.wav");
    SetSoundVolume(coinSound, 0.4f);
}

void UnloadCoinSound(void)
{
    UnloadSound(coinSound);
    CloseAudioDevice();
}

void UpdateCoins(void)
{
    animTime += GetFrameTime();
}

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
                {
                    float pulse = 0.2f * sinf(animTime * 6.0f) + 0.8f;
                    float radius = (TILE_SIZE / 4.0f) * pulse;

                    Color glow = (Color){255, 220, 100, (unsigned char)(180 + 50 * pulse)};
                    DrawCircle(posX + TILE_SIZE / 2, posY + TILE_SIZE / 2, radius + 3, glow);
                    DrawCircle(posX + TILE_SIZE / 2, posY + TILE_SIZE / 2, radius, GOLD);
                }
                break;

                default:
                    break;
            }
        }
    }
}

void CheckCoinCollision(int playerX, int playerY)
{
    int offsetX = 50;
    int offsetY = 50;

    int col = (playerX - offsetX) / TILE_SIZE;
    int row = (playerY - offsetY) / TILE_SIZE;

    if (row >= 0 && row < MAP_ROWS && col >= 0 && col < MAP_COLS)
    {
        if (map[row][col] == TILE_COIN)
        {
            map[row][col] = TILE_PATH;
            PlaySound(coinSound);
        }
    }
}
