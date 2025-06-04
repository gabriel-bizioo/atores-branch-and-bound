#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <limits.h>
#include "branch_bound.h"
#include "problema.h"
#include "util.h"

int corte_viabilidade = 1;
int corte_otimalidade = 1;
int usar_bound_professor = 0;

void imprime_uso(const char *program_name) {
    fprintf(stderr, "Uso: %s [opcoes]\n", program_name);
    fprintf(stderr, "Opcoes:\n");
    fprintf(stderr, "  -f    Desabilita cortes por viabilidade\n");
    fprintf(stderr, "  -o    Desabilita cortes por otimalidade\n");
    fprintf(stderr, "  -a    Usa funcao limitante do professor\n");
    fprintf(stderr, "  -h    Mostra esta ajuda\n");
}

void parse_arguments(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "foah")) != -1) {
        switch (opt) {
            case 'f':
                corte_viabilidade = 0;
                break;
            case 'o':
                corte_otimalidade = 0;
                break;
            case 'a':
                usar_bound_professor = 1;
                break;
            case 'h':
                imprime_uso(argv[0]);
                exit(0);
            case '?':
                imprime_uso(argv[0]);
                exit(1);
        }
    }
}

problema *le_instancia() {
    int l, m, n;

    if (scanf("%d %d %d", &l, &m, &n) != 3) {
        fprintf(stderr, "Erro: Falha ao ler parametros iniciais\n");
        exit(1);
    }

    if (l <= 0 || m <= 0 || n <= 0) {
        fprintf(stderr, "Erro: Parametros devem ser positivos\n");
        exit(1);
    }

    problema *p = cria_problema(l, n);

    for (int i = 0; i < m; i++) {
        ator a;

        int r, s;
        if (scanf("%d %d %d", &a.valor, &r, &s) != 3) {
            fprintf(stderr, "Erro: Falha ao ler dados do ator %d\n", i + 1);
            exit(1);
        }

        if (a.valor < 0 || r < 0 || s < 0) {
            fprintf(stderr, "Erro: Valores negativos para ator %d\n", i + 1);
            exit(1);
        }

        lista_int_init(&a.P_a);
        lista_int_init(&a.S_a);

        for (int j = 0; j < r; j++) {
            int personagem;
            if (scanf("%d", &personagem) != 1) {
                fprintf(stderr, "Erro: Falha ao ler personagem para ator %d\n", i + 1);
                exit(1);
            }

            if (personagem < 1 || personagem > n) {
                fprintf(stderr, "Erro: Personagem %d invalido para ator %d\n", personagem, i + 1);
                exit(1);
            }

            lista_int_add(&a.P_a, personagem);
        }

        for (int j = 0; j < s; j++) {
            int grupo;
            if (scanf("%d", &grupo) != 1) {
                fprintf(stderr, "Erro: Falha ao ler grupo para ator %d\n", i + 1);
                exit(1);
            }

            if (grupo < 1 || grupo > l) {
                fprintf(stderr, "Erro: Grupo %d invalido para ator %d\n", grupo, i + 1);
                exit(1);
            }

            lista_int_add(&a.S_a, grupo);
        }

        lista_ator_add(&p->A, a);
    }

    return p;
}

void imprime_solucao(problema *p) {
    if (!p->E) {
        printf("INVIAVEL\n");
        return;
    }

    for (int i = 0; i < p->E->X.size; i++) {
        if (i > 0) printf(" ");
        printf("%d", p->E->X.itens[i]);
    }
    printf("\n%d\n", p->E->custo);
}

int main(int argc, char *argv[]) {
    parse_arguments(argc, argv);

    problema *p = le_instancia();

    estado *inicial = cria_estado_inicial(p);

    int (*bound_function)(problema*, estado*);
    if (usar_bound_professor) {
        bound_function = B_dada;
    } else {
        bound_function = B_melhorada;
    }

    clock_t tempo_inicio = clock();
    branch_bound(p, inicial, bound_function);
    clock_t tempo_fim = clock();

    double tempo_total = (double)(tempo_fim - tempo_inicio)/CLOCKS_PER_SEC;
    fprintf(stderr, "Algoritmo Terminou.\n");
    fprintf(stderr, "  Tempo: %.6f segundos\n  Nós explorados: %d\n\n",
            tempo_total, p->nos_explorados);

    imprime_solucao(p);

    destroi_estado(inicial);
    destroi_problema(p);

    return 0;
}
