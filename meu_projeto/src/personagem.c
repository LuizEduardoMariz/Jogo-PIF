#include "personagem.h"
#include "mapa.h"
#include "raylib.h"
#include <stdio.h>

void InitPlayer(Jogador *p, int startGridX, int startGridY) {
    p->x = startGridX;
    p->y = startGridY;
    p->vivo = true;
    p->moedas = 0;

    p->sprite = LoadTexture("assets/player.png");
    p->tileSize = 32; 
}

void UpdatePlayer(Jogador *p, int key, Mapa *m) {
    if (!p->vivo) return;

    switch (key) {
        case KEY_W: MovePlayer(p, 0, -1, m); break;
        case KEY_S: MovePlayer(p, 0,  1, m); break;
        case KEY_A: MovePlayer(p, -1, 0, m); break;
        case KEY_D: MovePlayer(p,  1, 0, m); break;
    }

    if (mapa_get(m, p->y, p->x) == CEL_MOEDA) {
        p->moedas++;
        mapa_set(m, p->y, p->x, CEL_VAZIA);
    }
}

void MovePlayer(Jogador *p, int dx, int dy, const Mapa *m) {
    int newX = p->x + dx;
    int newY = p->y + dy;
    if (newX < 0 || newX >= m->colunas || newY < 0 || newY >= m->linhas) return;
    if (mapa_get(m, newY, newX) == CEL_PAREDE) return;
    p->x = newX;
    p->y = newY;
}

void DrawPlayer(const Jogador *p) {
    // Desenha com Raylib em vez de printf
    DrawTexture(p->sprite, p->x * p->tileSize, p->y * p->tileSize, WHITE);
}

void FreePlayer(Jogador *p) {
    UnloadTexture(p->sprite);
}
