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

int B_dada(estado_t *estado_t) {

    return 0;
}

estado_t *copia_estado(estado_t *estado) {
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

void branch_and_bound(estado_t *estado, ator *atores, int nAtores, int *func(int, int*, int)) {
    void *bound = func;
    int menor_custo = INFINITY;

    if((!estado->nPapeis) && (!estado->nAtores) && (!estado->nGrupos)) {

        //O(infinito e alem) se der tempo implementar com tabela hash
        for(int i=nAtores; i>0; i--) {
            ator ator = atores[i];
            int nPapeis = ator.nPapeis;

            for(int j=0; j < nPapeis; j++) {
                if(!estado->papeis[ator.iPapeis[j]]) {
                    estado_t *novo_estado = copia_estado(estado);
                    //ator *novo_atores = copia_atores(atores)

                    int nGrupos = ator.nGrupos;
                    for(int z=0; z<nGrupos; z++) {
                        if(!novo_estado->grupos[ator.iGrupos[z]]) // Aaa se desse pra fazer em python...
                            novo_estado->grupos[ator.iGrupos[z]] = 1;
                    }
                    //adiciona(novo_estado->atores, ator);
                    //remove(atores, ator);

                    int novo_nAtores = nAtores - 1;
                    branch_and_bound(novo_estado, atores, novo_nAtores--, func);
                }
            }
        }
    }

}
