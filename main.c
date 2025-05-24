#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    int custoTotal;

    int nPapeis;
    int nGrupos;
    int nAtores;

    int *papeis;
    int *grupos;
    int *atores;
} estado_t;

typedef struct Ator {
    int valor;

    int nPapeis;
    int nGrupos;

    int *iPapeis;
    int *iGrupos;
} ator;

int min(int *valores, int n) {
    int min = valores[0];
    int atual;

    for(int i = 1; i < n; i++) {
        atual = valores[i];
        if(atual < min)
            min = atual;
    }

    return min;
}

int B_dada(int c_atual, int *valores, int n, int n_restantes) {

    return c_atual + min(valores, n) * n_restantes;
}

estado_t *copiaestado(estado_t *estado) {
    estado_t *copia = malloc(sizeof(estado_t));
    int nPapeis = estado->nPapeis;
    int nGrupos = estado->nGrupos;
    int nAtores = estado->nAtores;

    copia->atores = malloc(sizeof(ator)*nAtores);
    for(int i=0; i < nPapeis; i++)
        copia->atores[i] = estado->atores[i];

    copia->grupos = malloc(sizeof(ator)*nGrupos);
    for(int i=0; i < nPapeis; i++)
        copia->grupos[i] = estado->grupos[i];

    copia->papeis = malloc(sizeof(ator)*nAtores);
    for(int i=0; i < nPapeis; i++)
        copia->grupos[i] = estado->grupos[i];

    return copia;
}

void branch_and_bound(estado_t *estado, ator *atores, int nAtores,
        int *func(int, int*, int)) {
    void *bound = func;
    int menor_custo = INFINITY;
    
    if((!estado->nPapeis) && (!estado->nAtores) && (!estado->nGrupos)) {
        estado_t *novo_estado = copiaestado(estado);

        for(int i = 0; i < nAtores; i++) {
            
        }
    }

}
