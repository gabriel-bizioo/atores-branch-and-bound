#include "problema.h"
#include <stdlib.h>
#include <limits.h>

void lista_ator_init(lista_ator *list) {
    list->ator = NULL;
    list->size = 0;
}

void lista_ator_add(lista_ator *list, ator item) {
    list->ator = realloc(list->ator, (list->size + 1) * sizeof(ator));
    list->ator[list->size] = item;
    list->size++;
}

void lista_ator_destroy(lista_ator *list) {
    for (int i = 0; i < list->size; i++) {
        lista_int_destroy(&list->ator[i].S_a);
        lista_int_destroy(&list->ator[i].P_a);
    }
    if (list->ator) {
        free(list->ator);
        list->ator = NULL;
    }
    list->size = 0;
}

estado *cria_estado_inicial(problema *p) {
    estado *e = malloc(sizeof(estado));
    e->custo = 0;
    e->S_e = lista_int_copy(&p->S);
    lista_int_init(&e->X);
    return e;
}

estado *copia_estado(estado *e) {
    if (!e) return NULL;

    estado *copy = malloc(sizeof(estado));
    copy->custo = e->custo;
    copy->S_e = lista_int_copy(&e->S_e);
    copy->X = lista_int_copy(&e->X);
    return copy;
}

void destroi_estado(estado *e) {
    if (!e) return;

    lista_int_destroy(&e->S_e);
    lista_int_destroy(&e->X);
    free(e);
}

problema *cria_problema(int l, int n) {
    problema *p = malloc(sizeof(problema));
    p->otim = INT_MAX;
    p->nos_explorados = 0;

    lista_int_init(&p->S);
    lista_ator_init(&p->A);
    lista_int_init(&p->P);

    for (int i = 1; i <= l; i++)
        lista_int_add(&p->S, i);
    for (int i = 1; i <= n; i++)
        lista_int_add(&p->P, i);

    p->E = NULL; // Solucao viavel do problema
    return p;
}

void destroi_problema(problema *p) {
    if (!p) return;

    lista_int_destroy(&p->S);
    lista_ator_destroy(&p->A);
    lista_int_destroy(&p->P);

    if (p->E)
        destroi_estado(p->E);

    free(p);
}
