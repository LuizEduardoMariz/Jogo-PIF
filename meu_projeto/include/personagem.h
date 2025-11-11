#ifndef PERSONAGEM_H
#define PERSONAGEM_H

typedef struct {
    int x;
    int y;
    int vivo;
    int moedas;
} Jogador;

void InitPlayer(Jogador *p, int startGridX, int startGridY);
void DrawPlayer(Jogador *p);
void UpdatePlayer(Jogador *p, int key);

#endif
