#ifndef __UTIL__
#define __UTIL__

typedef struct lista_int {
    int *itens;
    int size;
} lista_int;

void lista_int_init(lista_int *list);
void lista_int_add(lista_int *list, int item);
void lista_int_remove(lista_int *list, int item);
lista_int lista_int_copy(lista_int *src);
void lista_int_destroy(lista_int *list);



#endif
