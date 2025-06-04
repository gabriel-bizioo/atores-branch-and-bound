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

    // Itera por todos os atores ainda nao escolhidos
    for (int i = 0; i < p->A.size; ++i) {
        ator a = p->A.ator[i];
        // Pula atores ja escolhidos
        int pular = 0;
        for (int j = 0; j < e->X.size; ++j) {
            if(e->X.itens[j] == i + 1)
                pular = 1;
            break;
        }
        if(pular)
            continue;

        // Verifica se o ator pode fazer o papel sendo testado atualmente
        for (int j = 0; j < a.P_a.size; ++j) {

            // Se pode, faz a chamada recursiva para o proximo estado
            if ((e->X.size+1) == a.P_a.itens[j]) {

                estado *novo_e = copia_estado(e);
                novo_e->custo += a.valor;
                lista_int_add(&novo_e->X, (i+1));
                for (int z = 0; z < a.S_a.size; ++z)
                    lista_int_remove(&novo_e->S_e, a.S_a.itens[z]);

                if (p->otim >= bound(p, novo_e)) // Adicionar verificacao da flag -o
                    branch_bound(p, novo_e, bound);
                destroi_estado(novo_e);
            }
        }
    }
}
