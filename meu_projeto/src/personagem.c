#include "personagem.h"
#include "mapa.h"
#include "cli-lib.h"
#include <stdio.h>

void InitPlayer(Jogador *p, int startGridX, int startGridY)
{
    p->x = startGridX;
    p->y = startGridY;
    p->vivo = 1;
    p->moedas = 0;
}

void DrawPlayer(Jogador *p)
{
    screenGotoxy(p->x, p->y);
    printf("P");
}

void UpdatePlayer(Jogador *p, int key)
{
    switch (key) {
        case 'w': p->y--; break;
        case 's': p->y++; break;
        case 'a': p->x--; break;
        case 'd': p->x++; break;
    }

    if (p->x < 0) p->x = 0;
    if (p->x >= MAP_COLS) p->x = MAP_COLS - 1;
    if (p->y < 0) p->y = 0;
    if (p->y >= MAP_ROWS) p->y = MAP_ROWS - 1;

    CheckCoinCollision(p->x, p->y);
}
