/* 
 * File:   Huffman.h
 * Código baseado na Aula do Paulovich
 *
 * 
 */

#ifndef ARVOREBINARIA_H
#define	ARVOREBINARIA_H

typedef struct NO{
  int simbolo;
  int frequencia;
  struct NO *filhoesq;
  struct NO *filhodir;
} NO;

typedef struct ARVORE_BINARIA {
  NO *raiz;
} ARVORE_BINARIA;

ARVORE_BINARIA *criar_arvore();
void apagar_arvore(ARVORE_BINARIA **arvore);
NO *criar_raiz(ARVORE_BINARIA *arvore, NO *no);
int vazia_arvore(ARVORE_BINARIA *arvore);

#endif	/* ARVOREBINARIA_H */

