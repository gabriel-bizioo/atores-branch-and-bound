#include "branch_bound.h"
#include <stdio.h>
#include <limits.h>

int B_dada(problema *p, estado *e) {
    int custo_atual = e->custo;
    int personagens_restantes = p->P.size - e->X.size;

    if (personagens_restantes == 0)
        return custo_atual;

    int min_valor = INT_MAX;
    for (int i = 0; i < p->A.size; i++) {
        //pula atores ja escolhidos
        int pular = 0;
        for (int j = 0; j < e->X.size; j++) {
            if (e->X.itens[j] == i + 1) {
                pular = 1;
                break;
            }
        }
        if (!pular && p->A.ator[i].valor < min_valor)
            min_valor = p->A.ator[i].valor;
    }

    if (min_valor == INT_MAX)
        return INT_MAX;

    return custo_atual + (personagens_restantes * min_valor);
}

int B_melhorada(problema *p, estado *e) {
    int bound = e->custo;
    int personagens_restantes = p->P.size - e->X.size;

    if (personagens_restantes == 0) {
        return bound;
    }

    // TODO: Implement your improved heuristic here
    // Ideas:
    // 1. Consider uncovered groups and minimum cost to cover them
    // 2. Use character-specific minimum costs instead of global minimum
    // 3. Consider actor efficiency (groups covered per cost)

    // For now, fall back to B_dada
    return B_dada(p, e);
}

/*
 * A FAZER:
 *  - cortes por viabilidade e otimalidade
 */
void branch_bound(problema *p, estado *e, int (*bound)(problema*, estado*)) {
    p->nos_explorados++;

    // Base da recursao (todos os personagens escolhidos)
    if ((e->S_e.size == 0) && !(p->P.size - e->X.size)) {
        if(e->custo <= p->otim) {
            p->otim = e->custo;
            if(p->E != NULL)
                destroi_estado(p->E);
            p->E = copia_estado(e);
        }
        return;
    }

    // solucao inviavel
    if(!(p->P.size - e->X.size))
        return;

    int tam_Cl = p->A.size - e->X.size;
    printf("%d\n", tam_Cl);
    ator *Cl[tam_Cl];
    int count = 0;
    for(int i = 0; i < p->A.size; ++i) {
        int pular = 0;
        for (int j = 0; j < e->X.size; ++j) {
            if(e->X.itens[j] == i + 1)
                pular = 1;
            break;
        }
        if(pular)
            continue;
        printf("Ator %d em Cl\n", p->A.ator[i].id);
        Cl[count] = &p->A.ator[i];
        count++;
    }

    int nextbound[tam_Cl];
    int nextchoice[tam_Cl];
    for(int i = 0; i < tam_Cl; ++i) {

        estado *novo_e = copia_estado(e);
        novo_e->custo += Cl[i]->valor;
        lista_int_add(&novo_e->X, Cl[i]->id);
        for (int j = 0; j < Cl[i]->S_a.size; ++j)
            lista_int_remove(&novo_e->S_e, Cl[i]->S_a.itens[j]);

        nextchoice[i] = Cl[i]->id;
        nextbound[i] = bound(p, novo_e);
        printf("i: %d\tbound: %d\tchoice: %d\n", i, nextbound[i], nextchoice[i]);
        destroi_estado(novo_e);
    }

    // "Sort nextchoice and nextbound so that nextbound is in decreasing order"
    
    for(int i = 0; i < tam_Cl; ++i) {
        if(nextbound[i] >= p->otim)
            continue;

        estado *novo_e = copia_estado(e);
        novo_e->custo += Cl[i]->valor;
        lista_int_add(&novo_e->X, nextchoice[i]); // Teria que mudar a estrutura
        for (int j = 0; j < Cl[i]->S_a.size; ++j)
            lista_int_remove(&novo_e->S_e, Cl[i]->S_a.itens[j]);
        branch_bound(p, novo_e, bound);
    }
}
