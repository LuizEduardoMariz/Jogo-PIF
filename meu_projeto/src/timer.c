#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "timer.h"
#include "raylib.h"

static timer *head = NULL;

void adicionarTimer(timer *t) {
    if (!t) return;
    t->next = head;
    head = t;
}

void removerTimer(timer *t) {
    if (!t || !head) return;
    if (head == t) {
        head = head->next;
        return;
    }
    timer *aux = head;
    while (aux->next && aux->next != t) aux = aux->next;
    if (aux->next == t) aux->next = t->next;
}

timer *criarTimer(const char *nome, ModoTimer modo, float duracao, bool iniciar) {
    timer *t = malloc(sizeof(timer));
    if (!t) return NULL;
    strncpy(t->nome, nome ? nome : "timer", NOME_TAM - 1);
    t->nome[NOME_TAM - 1] = '\0';
    t->modo = modo;
    t->duracao = duracao > 0 ? duracao : 0;
    t->decorrido = 0;
    t->ativo = iniciar;
    t->finalizado = false;
    t->next = NULL;
    adicionarTimer(t);
    return t;
}

void destruirTimer(timer *t) {
    if (!t) return;
    removerTimer(t);
    free(t);
}

void destruirTodosTimers(void) {
    timer *atual = head;
    while (atual) {
        timer *prox = atual->next;
        free(atual);
        atual = prox;
    }
    head = NULL;
}

void iniciarTimer(timer *t) { if (t) t->ativo = true; }
void pararTimer(timer *t) { if (t) t->ativo = false; }

void resetarTimer(timer *t) {
    if (!t) return;
    t->decorrido = 0;
    t->finalizado = false;
}

void reiniciarTimer(timer *t) {
    if (!t) return;
    t->decorrido = 0;
    t->finalizado = false;
    t->ativo = true;
}

void definirDuracao(timer *t, float segundos) {
    if (t) t->duracao = (segundos >= 0) ? segundos : 0;
}

void atualizarTimer(timer *t, float dt) {
    if (!t || !t->ativo |
