#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "cli-lib.h"
#include "mapa.h"
#include "keyboard.h"

#define MAX_MONSTROS 3
#define TEMPO_TOTAL_NIVEL 60.0
#define TEMPO_POR_MOEDA 3.0

void verificar_condicoes_de_fim(Player *player, double tempo_inicial);

int main() {
    Player player;
    Monstro *monstros = NULL;
    double tempo_inicial, tempo_atual, dt;
    int moedas_no_inicio = 0;

    srand(time(NULL));
    keyboardInit();
    screenInit();

    player_inicializa(&player, 5, 5);
    monstros_inicializar(&monstros, MAX_MONSTROS);
    tempo_inicial = now_seconds();

    Mapa mapa;
    mapa_inicializar(&mapa, MAP_ROWS, MAP_COLS);

    while (player.vivo) {
        tempo_atual = now_seconds();
        dt = tempo_atual - tempo_inicial;

        char tecla = keyboardRead();
        switch (tecla) {
            case 'w': player_mover(&player, 0, -1, &mapa); break;
            case 's': player_mover(&player, 0, 1, &mapa); break;
            case 'a': player_mover(&player, -1, 0, &mapa); break;
            case 'd': player_mover(&player, 1, 0, &mapa); break;
            case 'q': player.vivo = false; break;
            default: break;
        }

        CheckCoinCollision(player.x, player.y);
        monstros_atualizar(monstros, MAX_MONSTROS, dt, &player);
        verificar_condicoes_de_fim(&player, tempo_inicial);

        screenClear();
        DrawGameMapASCII(&player, monstros, MAX_MONSTROS);

        printf("Moedas: %d | Tempo: %.1fs\n", player.moedas_coletadas, TEMPO_TOTAL_NIVEL - dt);
        struct timespec ts = {0, 100000000};
        nanosleep(&ts, NULL);

        if (TEMPO_TOTAL_NIVEL - dt <= 0) {
            printf("\nTempo esgotado!\n");
            break;
        }
    }

    monstros_liberar(&monstros);
    mapa_liberar(&mapa);
    keyboardClose();
    screenClose();
    printf("Fim de jogo!\n");
    return 0;
}

void verificar_condicoes_de_fim(Player *player, double tempo_inicial) {
    if (!player->vivo) {
        printf("Você foi derrotado!\n");
    } else if (player->moedas_coletadas >= 10) {
        printf("Parabéns! Você venceu coletando todas as moedas!\n");
        player->vivo = false;
    }
}
