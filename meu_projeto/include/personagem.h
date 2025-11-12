#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <stdbool.h>
#include "mapa.h"
#include "raylib.h"

typedef struct {
    int x, y;
    int moedas;
    bool vivo;
    Texture2D sprite;
    int tileSize;
} Jogador;

void InitPlayer(Jogador *p, int startGridX, int startGridY);
void MovePlayer(Jogador *p, int dx, int dy, const Mapa *m);
void UpdatePlayer(Jogador *p, int key, Mapa *m);
void DrawPlayer(const Jogador *p);
void FreePlayer(Jogador *p);

#endif
