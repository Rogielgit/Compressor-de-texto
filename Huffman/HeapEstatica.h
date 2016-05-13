/* 
 * File:   HeapEstatico.h
 * Author: paulovich
 *
 * Created on November 3, 2013, 11:10 AM
 */

#ifndef HEAPESTATICA_H
#define	HEAPESTATICA_H

#include "ArvoreBinaria.h"

typedef struct heap_estatica HEAP_ESTATICA;

HEAP_ESTATICA *criar_heap();
void apagar_heap(HEAP_ESTATICA **heap);

int inserir_heap(HEAP_ESTATICA *heap, NO *no);
NO *remover_heap(HEAP_ESTATICA *heap);

int cheia_heap(HEAP_ESTATICA *heap);
int vazia_heap(HEAP_ESTATICA *heap);
int tamanho_heap(HEAP_ESTATICA *heap);

#endif	/* HEAPESTATICO_H */

