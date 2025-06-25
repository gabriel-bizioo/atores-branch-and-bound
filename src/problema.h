#ifndef __PROBLEMA__
#define __PROBLEMA__
#include "util.h"


typedef struct {
    int id;
    int valor;
    lista_int S_a;
    lista_int P_a;
} ator;

typedef struct {
    ator *ator;
    int size;
} lista_ator;


typedef struct {
    int custo;
    lista_int S_e;
    lista_int X;
} estado;


typedef struct {
    int otim;
    int nos_explorados;
    lista_int S;
    lista_ator A;
    lista_int P;
    estado *E;
} problema;

estado *cria_estado_inicial(problema *p);
estado *copia_estado(estado *e);
void destroi_estado(estado *e);

problema *cria_problema(int l, int n);
void destroi_problema(problema *p);
void lista_ator_add(lista_ator *list, ator item);

#endif
