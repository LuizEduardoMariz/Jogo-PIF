#include "../include/mapa.h"
#include "../include/personagem.h"
#include <raylib.h>

int main(void)
{
    InitWindow(800, 600, "Labirinto Espacial - Som e Moedas Animadas");
    SetTargetFPS(60);

    InitCoinSound(); // 🔊 Inicia o som da moeda

    int playerX = 150;
    int playerY = 150;

    while (!WindowShouldClose())
    {
        // Movimento básico do jogador (exemplo)
        if (IsKeyDown(KEY_RIGHT)) playerX += 2;
        if (IsKeyDown(KEY_LEFT)) playerX -= 2;
        if (IsKeyDown(KEY_UP)) playerY -= 2;
        if (IsKeyDown(KEY_DOWN)) playerY += 2;

        // Atualiza e checa colisões
        UpdateCoins();
        CheckCoinCollision(playerX, playerY);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawGameMap();
            DrawCircle(playerX, playerY, 10, WHITE);
        EndDrawing();
    }

    UnloadCoinSound(); // 🔊 Libera o som
    CloseWindow();
    return 0;
}
