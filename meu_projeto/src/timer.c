#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "timer.h"
#include "raylib.h"

timer *head = NULL;

void adicionarTimer(timer *t) {
    if (t == NULL) {
        return;
    } else {
        t->next = head;
        head = t;
    }
}

void removerTimer(timer *t) {
    if (t == NULL || head == NULL) {
        return;
    } else if (head == t) {
        head = head->next;
        return;
    } else {
        timer *aux = head;
        while (aux->next != NULL && aux->next != t) {
            aux = aux->next;
        }

        if (aux->next == t) {
            aux->next = t->next;
        }
    }
}

timer *criarTimer(const char *nome, ModoTimer modo, float duracao, bool iniciar) {
    timer *t = (timer *)malloc(sizeof(timer));

    if (t == NULL) {
        return NULL;
    } else {
        if (nome != NULL) {
            strncpy(t->nome, nome, NOME_TAM - 1);
        } else {
            strncpy(t->nome, "timer", NOME_TAM - 1);
        }

        t->nome[NOME_TAM - 1] = '\0';
        t->modo = modo;

        if (duracao > 0) {
            t->duracao = duracao;
        } else {
            t->duracao = 0;
        }

        t->decorrido = 0;
        t->ativo = iniciar;
        t->finalizado = false;
        t->next = NULL;

        adicionarTimer(t);
        return t;
    }
}

void destruirTimer(timer *t) {
    if (t == NULL) {
        return;
    } else {
        removerTimer(t);
        free(t);
    }
}

void destruirTodosTimers(void) {
    if (head == NULL) {
        return;
    } else {
        timer *atual = head;

        while (atual != NULL) {
            timer *prox = atual->next;
            free(atual);
            atual = prox;
        }

        head = NULL;
    }
}

void iniciarTimer(timer *t) {
    if (t == NULL) {
        return;
    } else {
        t->ativo = true;
    }
}

void pararTimer(timer *t) {
    if (t == NULL) {
        return;
    } else {
        t->ativo = false;
    }
}

void resetarTimer(timer *t) {
    if (t == NULL) {
        return;
    } else {
        t->decorrido = 0;
        t->finalizado = false;
    }
}

void reiniciarTimer(timer *t) {
    if (t == NULL) {
        return;
    } else {
        t->decorrido = 0;
        t->finalizado = false;
        t->ativo = true;
    }
}

void definirDuracao(timer *t, float segundos) {
    if (t == NULL) {
        return;
    } else {
        if (segundos >= 0) {
            t->duracao = segundos;
        } else {
            t->duracao = 0;
        }
    }
}

void atualizarTimer(timer *t, float dt) {
    if (t == NULL) {
        return;
    } else if (t->ativo == false || t->finalizado == true) {
        return;
    } else {
        if (dt > 0) {
            t->decorrido += dt;
        }

        if (t->modo == REGRESSIVO) {
            if (t->decorrido >= t->duracao) {
                t->decorrido = t->duracao;
                t->finalizado = true;
                t->ativo = false;
            }
        } else {
            if (t->duracao > 0 && t->decorrido >= t->duracao) {
                t->finalizado = true;
                t->ativo = false;
            }
        }
    }
}

void atualizarTodosTimers(void) {
    if (head == NULL) {
        return;
    } else {
        float dt = GetFrameTime();
        timer *t = head;

        while (t != NULL) {
            atualizarTimer(t, dt);
            t = t->next;
        }
    }
}

float valorTimer(const timer *t) {
    if (t == NULL) {
        return 0;
    } else {
        if (t->modo == REGRESSIVO) {
            return t->duracao - t->decorrido;
        } else {
            return t->decorrido;
        }
    }
}

bool estaAtivo(const timer *t) {
    if (t == NULL) {
        return false;
    } else {
        return t->ativo;
    }
}

bool estaFinalizado(const timer *t) {
    if (t == NULL) {
        return false;
    } else {
        return t->finalizado;
    }
}

char *formatarTimer(const timer *t, char *buffer, int tamanho, bool comMs) {
    if (t == NULL || buffer == NULL) {
        return NULL;
    } else {
        float tempo;

        if (t->modo == REGRESSIVO) {
            tempo = t->duracao - t->decorrido;
        } else {
            tempo = t->decorrido;
        }

        if (tempo < 0) {
            tempo = 0;
        }

        int total = (int)tempo;
        int min = total / 60;
        int seg = total % 60;
        int ms  = (int)((tempo - total) * 1000);

        if (comMs) {
            snprintf(buffer, tamanho, "%02d:%02d.%03d", min, seg, ms);
        } else {
            snprintf(buffer, tamanho, "%02d:%02d", min, seg);
        }

        return buffer;
    }
}

bool salvarMelhorTempo(const char *arquivo, float valor) {
    FILE *f = fopen(arquivo, "wb");

    if (f == NULL) {
        return false;
    } else {
        fwrite(&valor, sizeof(float), 1, f);
        fclose(f);
        return true;
    }
}

float carregarMelhorTempo(const char *arquivo, bool *ok) {
    FILE *f = fopen(arquivo, "rb");

    if (f == NULL) {
        if (ok != NULL) {
            *ok = false;
        }
        return 0;
    } else {
        float valor = 0;
        size_t lido = fread(&valor, sizeof(float), 1, f);
        fclose(f);

        if (ok != NULL) {
            *ok = (lido == 1);
        }

        return valor;
    }
}

timer *criarTimerPrincipal(float segundos) {
    return criarTimer("principal", REGRESSIVO, segundos, true);
}

timer *criarTimerPerseguicao(void) {
    return criarTimer("perseguicao", REGRESSIVO, 3.0f, false);
}
