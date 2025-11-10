#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

#define NOME_TAM 32

typedef enum {
    CRONOMETRO = 0,   
    REGRESSIVO = 1    
} ModoTimer;

typedef struct timer {
    char nome[NOME_TAM];
    ModoTimer modo;
    float duracao;
    float decorrido;
    bool ativo;
    bool finalizado;
    struct timer *next;   
} timer;

extern timer *head;

void adicionarTimer(timer *t);
void removerTimer(timer *t);

timer *criarTimer(const char *nome, ModoTimer modo, float duracao, bool iniciar);
void destruirTimer(timer *t);
void destruirTodosTimers(void);

void iniciarTimer(timer *t);
void pararTimer(timer *t);
void resetarTimer(timer *t);
void reiniciarTimer(timer *t);
void definirDuracao(timer *t, float segundos);

void atualizarTimer(timer *t, float dt);
void atualizarTodosTimers(void);

float valorTimer(const timer *t);
bool  estaAtivo(const timer *t);
bool  estaFinalizado(const timer *t);
char *formatarTimer(const timer *t, char *buffer, int tamanho, bool comMs);

bool  salvarMelhorTempo(const char *arquivo, float valor);
float carregarMelhorTempo(const char *arquivo, bool *ok);

timer *criarTimerPrincipal(float segundos);
timer *criarTimerPerseguicao(void);

#endif
