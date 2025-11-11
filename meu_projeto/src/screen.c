#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "screen.h"
#include "cli-lib.h"

bool mapa_inicializar(Mapa *m, int linhas, int colunas) {
    if (!m || linhas <= 0 || colunas <= 0) return false;
    m->linhas = linhas;
    m->colunas = colunas;
    m->celulas = malloc(linhas * sizeof(char *));
    if (!m->celulas) return false;
    for (int i = 0; i < linhas; i++) {
        m->celulas[i] = malloc(colunas * sizeof(char));
        if (!m->celulas[i]) return false;
        memset(m->celulas[i], ' ', colunas);
    }
    return true;
}

void mapa_liberar(Mapa *m) {
    if (!m || !m->celulas) return;
    for (int i = 0; i < m->linhas; i++) free(m->celulas[i]);
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

void mapa_set(Mapa *m, int linha, int coluna, CellType tipo) {
    if (!m || !m->celulas) return;
    if (linha < 0 || linha >= m->linhas || coluna < 0 || coluna >= m->colunas) return;
    m->celulas[linha][coluna] = (char)tipo;
}

CellType mapa_get(const Mapa *m, int linha, int coluna) {
    if (!m || !m->celulas) return CEL_VAZIA;
    if (linha < 0 || linha >= m->linhas || coluna < 0 || coluna >= m->colunas) return CEL_VAZIA;
    return (CellType)m->celulas[linha][coluna];
}

bool monstros_inicializar(Monstro **m, int capacidade_inicial) {
    *m = malloc(capacidade_inicial * sizeof(Monstro));
    if (*m == NULL) return false;
    for (int i = 0; i < capacidade_inicial; i++) {
        (*m)[i].ativo = false;
        (*m)[i].x = 0;
        (*m)[i].y = 0;
        (*m)[i].tempo_spawn = 0.0;
    }
    return true;
}

void monstros_liberar(Monstro **m) {
    if (*m != NULL) {
        free(*m);
        *m = NULL;
    }
}

void monstros_atualizar(Monstro *monstros, int qtd, double dt, const Player *player) {
    double agora = now_seconds();
    for (int i = 0; i < qtd; i++) {
        if (!monstros[i].ativo) continue;
        int dx = (player->x > monstros[i].x) - (player->x
