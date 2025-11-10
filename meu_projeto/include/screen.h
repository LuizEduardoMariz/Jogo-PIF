#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>
#include <stdbool.h> 
#include "cli-lib.h"  

#define MAX_MONSTROS 128  
#define TEMPO_POR_MOEDA 3.0   
#define TEMPO_TOTAL_NIVEL 60 

typedef enum {
    CEL_VAZIA = 0,
    CEL_PAREDE,
    CEL_MOEDA,
    CEL_PLAYER,
    CEL_MONSTRO
} CellType;


typedef struct {
    int x, y;
    int moedas_coletadas;
    bool vivo;
    float speed;
    int dir_x, dir_y; 
} Player;

typedef struct {
    int x, y;
    bool ativo;
    double tempo_spawn;
    float speed;
} Monstro;

typedef struct Moeda {
    int x, y;
    struct Moeda *prox;
} Moeda;

typedef struct {
    int linhas, colunas;
    char **celulas;
} Mapa;

bool mapa_inicializar(Mapa *m, int linhas, int colunas);
void mapa_liberar(Mapa *m);
bool mapa_carregar_de_arquivo(Mapa *m, const char *caminho);
bool mapa_salvar_para_arquivo(const Mapa *m, const char *caminho);
CellType mapa_get(const Mapa *m, int linha, int coluna);
void mapa_set(Mapa *m, int linha, int coluna, CellType tipo);
Moeda *moeda_criar(int x, int y);
void moedas_insere_inicio(Moeda **head, int x, int y);
void moedas_remover(Moeda **head, Moeda *alvo);
Moeda *moedas_encontra_por_pos(Moeda *head, int x, int y);
void moedas_liberar_todas(Moeda **head);
int moedas_contar(Moeda *head);
bool monstros_inicializar(Monstro **m, int capacidade_inicial);
void monstros_liberar(Monstro **m);
int monstros_criar_na_direcao_player(Monstro *m, int qtd, int px, int py);
void monstros_desativar(Monstro *m, int idx);
void monstros_atualizar(Monstro *m, int qtd, double dt);
void player_inicializa(Player *p, int x, int y);
void player_mover(Player *p, int dx, int dy, const Mapa *m);
bool player_colide_monstro(const Player *p, Monstro *m, int qtd);
double now_seconds(void);
int rand_int(int min, int max);
void raylib_iniciar_janela(int largura, int altura, const char *titulo);
void raylib_finalizar_janela(void);

#endif
