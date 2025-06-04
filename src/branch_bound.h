#ifndef __BRANCH_BOUND__
#define __BRANCH_BOUND__
#include "problema.h"
#include <stdlib.h>

/*
 * Funcao de corte dada pelo professor para fins de comparacao
 */
int B_dada(problema *p, estado *e);

/*
 * Funcao de corte feita pelo grupo
 */
int B_melhorada(problema *p, estado *e);

void branch_bound(problema *p, estado *e, int (*bound)(problema*, estado*));
#endif
