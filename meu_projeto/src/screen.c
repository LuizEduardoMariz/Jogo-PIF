#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "screen.h"
#include "cli-lib.h"
#include "raylib.h"

bool mapa_inicializar(Mapa *m, int linhas, int colunas) {
    if (!m || linhas <= 0 || colunas <= 0)
        return false;

    m->linhas = linhas;
    m->colunas = colunas;

    m->celulas = malloc(linhas * sizeof(char *));
    if (!m->celulas)
        return false;

    for (int i = 0; i < linhas; i++) {
        m->celulas[i] = malloc(colunas * sizeof(char));
        if (!m->celulas[i])
            return false;
        memset(m->celulas[i], ' ', colunas);
    }

    return true;
}

void mapa_liberar(Mapa *m) {
    if (!m || !m->celulas)
        return;

    for (int i = 0; i < m->linhas; i++)
        free(m->celulas[i]);
    free(m->celulas);
    m->celulas = NULL;
    m->linhas = 0;
    m->colunas = 0;
}

bool mapa_carregar_de_arquivo(Mapa *m, const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return false;

    int linhas, colunas;
    fscanf(f, "%d %d\n", &linhas, &colunas);

    if (!mapa_inicializar(m, linhas, colunas)) {
        fclose(f);
        return false;
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int c = fgetc(f);
            if (c == '\n' || c == '\r') { j--; continue; }
            m->celulas[i][j] = (char)c;
        }
    }

    fclose(f);
    return true;
}

bool mapa_salvar_para_arquivo(const Mapa *m, const char *caminho) {
    if (!m || !m->celulas)
        return false;

    FILE *f = fopen(caminho, "w");
    if (!f)
        return false;

    fprintf(f, "%d %d\n", m->linhas, m->colunas);
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++)
            fputc(m->celulas[i][j], f);
        fputc('\n', f);
    }

    fclose(f);
    return true;
}

CellType mapa_get(const Mapa *m, int linha, int coluna) {
    if (!m || !m->celulas)
        return CEL_VAZIA;
    if (linha < 0 || linha >= m->linhas || coluna < 0 || coluna >= m->colunas)
        return CEL_VAZIA;
    return (CellType)m->celulas[linha][coluna];
}

void mapa_set(Mapa *m, int linha, int coluna, CellType tipo) {
    if (!m || !m->celulas)
        return;
    if (linha < 0 || linha >= m->linhas || coluna < 0 || coluna >= m->colunas)
        return;
    m->celulas[linha][coluna] = (char)tipo;
}

Moeda *moeda_criar(int x, int y) {
}

void moedas_insere_inicio(Moeda **head, int x, int y) {
}

void moedas_remover(Moeda **head, Moeda *alvo) {
}

Moeda *moedas_encontra_por_pos(Moeda *head, int x, int y) {
}

void moedas_liberar_todas(Moeda **head) {
}

int moedas_contar(Moeda *head) {
}

bool monstros_inicializar(Monstro **m, int capacidade_inicial) {
*m = (Monstro *)malloc(capacidade_inicial * sizeof(Monstro));
    if (*m == NULL) return false;
    for (int i = 0; i < capacidade_inicial; i++) {
        (*m)[i].ativo = false;
        (*m)[i].x = 0;
        (*m)[i].y = 0;
        (*m)[i].tempo_spawn = 0.0;
        (*m)[i].speed = 1.0f;
    }
    return true;
}

void monstros_liberar(Monstro **m) {
    if (*m != NULL) {
        free(*m);
        *m = NULL;
    } 
}

int monstros_criar_na_direcao_player(Monstro *m, int qtd, int px, int py) {
    for (int i = 0; i < qtd; i++) {
        if (!m[i].ativo) {
            m[i].ativo = true;
            m[i].tempo_spawn = now_seconds();
            m[i].speed = 1.0f;
            int dir = rand_int(0, 3);
            if (dir == 0) { m[i].x = px + 1; m[i].y = py; }
            else if (dir == 1) { m[i].x = px - 1; m[i].y = py; }
            else if (dir == 2) { m[i].x = px; m[i].y = py + 1; }
            else { m[i].x = px; m[i].y = py - 1; }
            return i;   
        }
}

void monstros_desativar(Monstro *m, int idx) {
    m[idx].ativo = false;
    m[idx].x = 0;
    m[idx].y = 0;
    m[idx].tempo_spawn = 0.0;
}

void monstros_atualizar(Monstro *m, int qtd, double dt) {
    void monstros_atualizar(Monstro *monstros, int qtd, double dt) {
    double agora = now_seconds();

    for (int i = 0; i < qtd; i++) {
        if (!monstros[i].ativo) continue;

        // faz o mosntro seguir o player
        int dx = (player.x > monstros[i].x) - (player.x < monstros[i].x);
        int dy = (player.y > monstros[i].y) - (player.y < monstros[i].y);
        monstros[i].x += dx;
        monstros[i].y += dy;

        if (monstros[i].x == player.x && monstros[i].y == player.y) {
            player.vivo = false; // Se alcançou acaba o jogo
        }

        if (agora - monstros[i].tempo_spawn >= TEMPO_POR_MOEDA) {
            monstros[i].ativo = false; // tempo do monstro
        }
    }
}
}

void player_inicializa(Player *p, int x, int y) {
    if (!p) return;
    p->x = x;
    p->y = y;
    p->moedas_coletadas = 0;
    p->vivo = 1;
}

void player_mover(Player *p, int dx, int dy, const Mapa *m) {
    if (!p || !m || !m->celulas || !p->vivo)
        return;

    int novo_x = p->x + dx;
    int novo_y = p->y + dy;

    if (novo_y < 0 || novo_y >= m->linhas || novo_x < 0 || novo_x >= m->colunas)
        return; //impede de sair do mapa

    CellType destino = mapa_get(m, novo_y, novo_x);

    if (destino == CEL_PAREDE)
        return;   //define as paredes

    if (destino == CEL_MOEDA) {
        p->moedas_coletadas++;
        mapa_set((Mapa *)m, novo_y, novo_x, CEL_VAZIA); //mecanica de moeda coletada
    }
    p->x = novo_x;
    p->y = novo_y; //atualiza posição
}
}


bool player_colide_monstro(const Player *p, Monstro *m, int qtd) {
    if (!p || !monstros || qtd <= 0)
        return false;

    for (int i = 0; i < qtd; i++) {
        if (!monstros[i].ativo)
            continue;
        if (p->x == monstros[i].x && p->y == monstros[i].y)
            return true; // 💀 Colisão detectada
    }
    return false;
}

double now_seconds(void) {
}

int rand_int(int min, int max) {
}

void raylib_iniciar_janela(int largura, int altura, const char *titulo) {
}

void raylib_finalizar_janela(void) {
}

void verificar_condicoes_de_fim(Player *p, double tempo_inicial) {
    double agora = now_seconds();
    double tempo_decorrido = agora - tempo_inicial;

    if (tempo_decorrido >= TEMPO_TOTAL_NIVEL) {
        p->vivo = false;
        printf("\nTempo esgotado! Game Over.\n");
    }

    if (p->moedas_coletadas >= 10) {
        printf("\nVocê coletou todas as moedas! Vitória!\n");
        p->vivo = false;
    }
}
