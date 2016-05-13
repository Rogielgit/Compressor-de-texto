#include "ArvoreBinaria.h"

#include <stdio.h>
#include <stdlib.h>

ARVORE_BINARIA *criar_arvore() {
  ARVORE_BINARIA *arv = (ARVORE_BINARIA *) malloc(sizeof (ARVORE_BINARIA));

  if (arv != NULL) {
    arv->raiz = NULL;
  }

  return arv;
}

NO *criar_raiz(ARVORE_BINARIA *arvore, NO *no) {
  arvore->raiz = no;
  return arvore->raiz;
}

int vazia_arvore(ARVORE_BINARIA *arvore) {
  return (arvore->raiz == NULL);
}

void apagar_arvore_aux(NO *raiz) {
  if (raiz != NULL) {
    apagar_arvore_aux(raiz->filhoesq);
    apagar_arvore_aux(raiz->filhodir);
    free(raiz);
  }
}

void apagar_arvore(ARVORE_BINARIA **arvore) {
  apagar_arvore_aux((*arvore)->raiz);
  free(*arvore);
  *arvore = NULL;
}