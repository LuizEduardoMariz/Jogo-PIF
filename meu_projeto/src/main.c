#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "cli-lib.h"
#include "mapa.h"
#include "keyboard.h"


//#define MAX_MONSTROS 3
//#define TEMPO_TOTAL_NIVEL 60.0
#define TEMPO_POR_MOEDA 3.0

void verificar_condicoes_de_fim(Player *player, double tempo_inicial);

int main() {
    Player player;
    Monstro *monstros = NULL;
    double tempo_inicial;

    srand(time(NULL));

    player_inicializa(&player, 5, 5);
    monstros_inicializar(&monstros, MAX_MONSTROS);
    tempo_inicial = now_seconds();

    keyboardInit();

    while (player.vivo) {
        double agora = now_seconds();
        double dt = agora - tempo_inicial;
        char ch = keyboardRead();

        if (ch == 'w') player.y -= 1;
        else if (ch == 's') player.y += 1;
        else if (ch == 'a') player.x -= 1;
        else if (ch == 'd') player.x += 1;

        CheckCoinCollision(player.x, player.y);
        monstros_atualizar(monstros, MAX_MONSTROS, dt, &player);
        verificar_condicoes_de_fim(&player, tempo_inicial);

        screenClear();
        DrawGameMapASCII(&player, monstros, MAX_MONSTROS);

        struct timespec ts = {0, 50000000};
        nanosleep(&ts, NULL);
    }

    keyboardClose();
    monstros_liberar(&monstros);
    printf("Fim de jogo!\n");
    return 0;
}
