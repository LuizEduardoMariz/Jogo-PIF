#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "raylib.h"
#include "mapa.h"

#define MAX_MONSTROS 20
#define TEMPO_TOTAL_NIVEL 60.0
#define TEMPO_POR_MOEDA 3.0

int main() {
    Player player;
    Monstro *monstros = NULL;
    Moeda *moedas = NULL;
    double tempo_inicial;

    srand(time(NULL));

    player_inicializa(&player, 100, 100);
    monstros_inicializar(&monstros, MAX_MONSTROS);
    tempo_inicial = now_seconds();

    InitWindow(800, 600, "Jogo das Moedas");
    SetTargetFPS(60);
    InitCoinSound();

    while (!WindowShouldClose() && player.vivo) {
        double agora = now_seconds();
        double dt = agora - tempo_inicial;

        if (IsKeyPressed(KEY_UP)) player.y -= 10;
        if (IsKeyPressed(KEY_DOWN)) player.y += 10;
        if (IsKeyPressed(KEY_LEFT)) player.x -= 10;
        if (IsKeyPressed(KEY_RIGHT)) player.x += 10;

        CheckCoinCollision(player.x, player.y);

        monstros_atualizar(monstros, MAX_MONSTROS, dt);
        verificar_condicoes_de_fim(&player, tempo_inicial);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawGameMap();
        DrawCircle(player.x, player.y, 8, BLUE);
        EndDrawing();
    }

    UnloadCoinSound();
    CloseWindow();
    monstros_liberar(&monstros);

    return 0;
}
