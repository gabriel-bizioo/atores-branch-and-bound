#ifndef __UTIL__
#define __UTIL__

typedef struct lista_int {
    int *itens;
    int size;
} lista_int;

void lista_int_add(lista_int list, int item);
void lista_int_remove(lista_int list, int item);



#endif
