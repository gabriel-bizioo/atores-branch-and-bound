#include "util.h"
#include <stdlib.h>
#include <string.h>

void lista_int_init(lista_int *list) {
    list->itens = NULL;
    list->size = 0;
}

void lista_int_add(lista_int *list, int item) {
    list->itens = realloc(list->itens, (list->size + 1) * sizeof(int));
    list->itens[list->size] = item;
    list->size++;
}

void lista_int_remove(lista_int *list, int item) {
    for (int i = 0; i < list->size; i++) {
        if (list->itens[i] == item) {
            for (int j = i; j < list->size - 1; j++) {
                list->itens[j] = list->itens[j + 1];
            }
            list->size--;

            if (list->size == 0) {
                free(list->itens);
                list->itens = NULL;
            }
            else
                list->itens = realloc(list->itens, list->size * sizeof(int));
            return;
        }
    }
}

void lista_int_destroy(lista_int *list) {
    if (list->itens) {
        free(list->itens);
        list->itens = NULL;
    }
    list->size = 0;
}

lista_int lista_int_copy(lista_int *src) {
    lista_int copy;
    lista_int_init(&copy);
    
    if (src->size > 0) {
        copy.itens = malloc(src->size * sizeof(int));
        copy.size = src->size;
        memcpy(copy.itens, src->itens, src->size * sizeof(int));
    }
    
    return copy;
}
