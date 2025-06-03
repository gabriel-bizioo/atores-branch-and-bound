#ifndef __BRANCH_BOUND__
#define __BRANCH_BOUND__
#include "problema.h"
#include <stdlib.h>

/*
 * Funcao de corte dada pelo professor para fins de comparacao
 */
void B_dada(estado *e);

/*
 * Funcao de corte feita pelo grupo
 */
void B_melhorada(estado *e);

void branch_bound(problema *p, estado *e, int (*bound)(estado*));
#endif
