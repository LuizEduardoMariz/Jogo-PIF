#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <raylib.h>

typedef struct Jogador{
    Vector2 position;
    Vector2 gridPosition;
    float speed;
    int size;
    Color color;
}Jogador;

void InitPlayer(Jogador *p, int startGridX, int startGridY);
void DrawPlayer(Jogador *p);
void UpdatePlayer(Jogador *p);

#endif