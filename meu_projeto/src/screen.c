#include "raylib.h"
#include "screens.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int x, y;
    int moedas_coletadas;
    bool vivo;
} Player;

typedef struct {
    int x, y;
    bool ativo;
    double tempo_spawn;
} Monstro;

typedef struct {
    int linhas, colunas;
    char **celulas;
} Mapa;

bool mapa_inicializar(Mapa *m, int linhas, int colunas) {
    if (!m || linhas <= 0 || colunas <= 0) return false;
    m->linhas = linhas;
    m->colunas = colunas;
    m->celulas = malloc(linhas * sizeof(char *));
    if (!m->celulas) return false;
    for (int i = 0; i < linhas; i++) {
        m->celulas[i] = malloc(colunas);
        if (!m->celulas[i]) return false;
        for (int j = 0; j < colunas; j++)
            m->celulas[i][j] = (i == linhas - 1) ? '#' : ' ';
    }
    return true;
}

void mapa_desenhar(const Mapa *m) {
    for (int i = 0; i < m->linhas; i++)
        for (int j = 0; j < m->colunas; j++)
            if (m->celulas[i][j] == '#')
                DrawRectangle(j * 32, i * 32, 32, 32, DARKBROWN);
}

void mapa_liberar(Mapa *m) {
    if (!m || !m->celulas) return;
    for (int i = 0; i < m->linhas; i++) free(m->celulas[i]);
    free(m->celulas);
    m->celulas = NULL;
}

bool monstros_inicializar(Monstro **m, int qtd) {
    *m = malloc(qtd * sizeof(Monstro));
    if (!*m) return false;
    for (int i = 0; i < qtd; i++) {
        (*m)[i].ativo = true;
        (*m)[i].x = GetRandomValue(100, 700);
        (*m)[i].y = GetRandomValue(100, 400);
        (*m)[i].tempo_spawn = GetTime();
    }
    return true;
}

void monstros_desenhar(Monstro *monstros, int qtd) {
    for (int i = 0; i < qtd; i++)
        if (monstros[i].ativo)
            DrawCircle(monstros[i].x, monstros[i].y, 15, RED);
}

void monstros_atualizar(Monstro *monstros, int qtd, const Player *player) {
    for (int i = 0; i < qtd; i++) {
        if (!monstros[i].ativo) continue;
        if (player->x > monstros[i].x) monstros[i].x++;
        if (player->x < monstros[i].x) monstros[i].x--;
        if (player->y > monstros[i].y) monstros[i].y++;
        if (player->y < monstros[i].y) monstros[i].y--;
    }
}

GameScreen RunGameScreen(Music gameMusic) {
    const int qtd_monstros = 3;
    Mapa mapa;
    Player player = {400, 300, 0, true};
    Monstro *monstros = NULL;
    double delta = 0.0;
    double ultimoTempo = GetTime();
    mapa_inicializar(&mapa, 15, 25);
    monstros_inicializar(&monstros, qtd_monstros);
    while (!WindowShouldClose()) {
        UpdateMusicStream(gameMusic);
        delta = GetTime() - ultimoTempo;
        ultimoTempo = GetTime();
        if (IsKeyDown(KEY_A)) player.x -= 4;
        if (IsKeyDown(KEY_D)) player.x += 4;
        if (IsKeyDown(KEY_W)) player.y -= 4;
        if (IsKeyDown(KEY_S)) player.y += 4;
        monstros_atualizar(monstros, qtd_monstros, &player);
        if (IsKeyPressed(KEY_ESCAPE)) {
            mapa_liberar(&mapa);
            free(monstros);
            return SCREEN_MENU;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        mapa_desenhar(&mapa);
        DrawCircle(player.x, player.y, 15, GOLD);
        monstros_desenhar(monstros, qtd_monstros);
        DrawText("Use WASD para mover | ESC para voltar", 20, 20, 20, WHITE);
        EndDrawing();
    }
    mapa_liberar(&mapa);
    free(monstros);
    return SCREEN_EXIT;
}
