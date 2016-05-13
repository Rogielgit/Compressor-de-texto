/*
 * File:   main.c
 * Author: paulovich
 *
 * Created on November 11, 2013, 9:30 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "Huffman.h"
#include "ArvoreBinaria.h"
#include "HeapEstatica.h"

/*
 *
 */
int main(int argc, char** argv) {
  char *msg = "SUSIE SAYS IT IS EASY";
  char codificado[1000];
  char decodificado[1000];

  //Criará a árvore Huffman com os respectivos campos.
  HUFFMAN *huffman = criar_huffman();

  criar_arvore_huffman(huffman, msg);
  criar_codigo(huffman);

  codificar(huffman, msg, codificado);
  decodificar(huffman, codificado, decodificado);

  printf("codificacao: %s\n", codificado);
  printf("decodificacao: %s\n", decodificado);

  apagar_huffman(&huffman);

  return (EXIT_SUCCESS);
}

