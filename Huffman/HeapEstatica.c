#include "HeapEstatica.h"

#include <stdlib.h>
#include <stdio.h>

#define TAM 100

struct heap_estatica {
  NO * vetor[TAM];
  int fim;
};

HEAP_ESTATICA *criar_heap() {
  HEAP_ESTATICA *heap = (HEAP_ESTATICA *) malloc(sizeof (HEAP_ESTATICA));
  if (heap != NULL) {
    heap->fim = -1;
  }
  return heap;
}

void apagar_heap(HEAP_ESTATICA **heap) {
  free(*heap);
  *heap = NULL;
}

void swap(HEAP_ESTATICA *heap, int i, int j) {
  NO *tmp = heap->vetor[i];
  heap->vetor[i] = heap->vetor[j];
  heap->vetor[j] = tmp;
}

void fix_up(HEAP_ESTATICA *heap) {
  int pos = heap->fim;
  int pai = (pos - 1) / 2;

  while (pos > 0 && heap->vetor[pos]->frequencia < heap->vetor[pai]->frequencia) {
    swap(heap, pos, pai);
    pos = pai;
    pai = (pai - 1) / 2;
  }
}

int inserir_heap(HEAP_ESTATICA *heap, NO *no) {
  if (!cheia_heap(heap)) {
    heap->fim++;
    heap->vetor[heap->fim] = no;
    fix_up(heap);
    return 1;
  }

  return 0;
}

void fix_down(HEAP_ESTATICA *heap) {
  int pos = 0;

  while (pos <= heap->fim / 2) {
    int filhoesq = 2 * pos + 1;
    int filhodir = 2 * pos + 2;

    int menorfilho;
    if (filhodir <= heap->fim &&
            heap->vetor[filhoesq]->frequencia > heap->vetor[filhodir]->frequencia) {
      menorfilho = filhodir;
    } else {
      menorfilho = filhoesq;
    }

    if (heap->vetor[pos]->frequencia < heap->vetor[menorfilho]->frequencia) {
      break;
    }

    swap(heap, pos, menorfilho);
    pos = menorfilho;
  }
}

NO *remover_heap(HEAP_ESTATICA *heap) {
  if (!vazia_heap(heap)) {
    NO *no = heap->vetor[0];
    heap->vetor[0] = heap->vetor[heap->fim];
    heap->fim--;
    fix_down(heap);
    return no;
  }
  return NULL;
}

int cheia_heap(HEAP_ESTATICA *heap) {
  return (heap->fim == TAM - 1);
}

int vazia_heap(HEAP_ESTATICA *heap) {
  return (heap->fim == -1);
}

int tamanho_heap(HEAP_ESTATICA *heap) {
  return heap->fim + 1;
}