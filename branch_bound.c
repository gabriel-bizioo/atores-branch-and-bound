#include "branch_bound.h"

/*
 * A FAZER: 
 *  - cortes por viabilidade e otimalidade
 *  - Funcoes auxiliares
 */
void branch_bound(problema *p, estado *e, int (*bound)(estado*)) {
    if(!(p->P.size - e->X.size)) {

        // Itera por todos os atores ainda nao escolhidos
        for(int i = 0; i < p->A.size; ++i) {
            ator a = p->A.ator[i];
            // Pula atores ja escolhidos (ta parecendo IA esses comentarios)
            int pular = 0;
            for(int j = 0; j < e->X.size; ++j) {
                if((i+1) == e->X.itens[j])
                    pular = 1;
                break;
            }
            if(pular)
                continue;

            // Verifica se o ator pode fazer o papel sendo testado atualmente
            for(int j = 0; j < a.P_a.size; ++i) {
                // Se pode, faz a chamada recursiva para o proximo estado
                if((e->X.size+1) == a.P_a.itens[j]) {
                    estado *novo_e = copia_estado(e);
                    novo_e->custo += a.valor;
                    lista_int_add(novo_e->X, (i+1));
                    for(int z = 0; z < a.S_a.size; ++z)
                        lista_int_remove(novo_e->X, a.S_a.itens[i]);
                    if( p->otim >= bound(novo_e))
                        branch_bound(p, e, bound);
                }
            }
        }
    }
    else if(e->S_e.size == 0) {
        if(e->custo <= p->otim) {
            p->otim = e->custo;
            if(p->E != NULL)
                destroi_estado(p->E);
            p->E = copia_estado(e);
            return;
        }
    }

    destroi_estado(e);
}
