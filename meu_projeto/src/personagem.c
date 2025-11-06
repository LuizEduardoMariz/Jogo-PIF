#include "personagem.h"
#include "mapa.h"
#include <raylib.h>

void InitPlayer(Jogador *p, int startGridX, int startGridY){
    p->gridPosition.x = startGridX;
    p->gridPosition.y = startGridY;
    
    p->position.x = 50 + p->gridPosition.x * TILE_SIZE + TILE_SIZE / 2;
    p->position.y = 50 + p->gridPosition.y * TILE_SIZE + TILE_SIZE / 2;

    p->speed = 2.0f;
    p->size = TILE_SIZE / 2;
    p->color = WHITE;
}

void DrawPlayer(Jogador *p){
    DrawCircleV(p->position, p->size, p->color);
}

void UpdatePlayer(Jogador *p){
    
}