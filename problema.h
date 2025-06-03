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

void lista_ator_add(lista_ator list, ator item);

typedef struct {
    int custo;
    lista_int S_e;

    /*
     * Talvez seja melhor guardar apenas o indice do ator aqui,
     * e acessar os dados atraves de "problema"
     */
    lista_int X;
} estado;

estado *copia_estado(estado *e);
void destroi_estado(estado *e);

typedef struct {
    int otim;
    lista_int S;
    lista_ator A;
    lista_int P;
    estado *E;
} problema;

problema *cria_problema(int l, int m, int n);

#endif
