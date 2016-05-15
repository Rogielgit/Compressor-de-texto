/* 
 * File:   Huffman.h
 * Código baseado na Aula do Paulovich
 *
 * 
 */

#ifndef HUFFMAN_H
#define	HUFFMAN_H

#include "ArvoreBinaria.h"

typedef struct huffman HUFFMAN;

HUFFMAN *criar_huffman();

void apagar_huffman(HUFFMAN **huffman);

void criar_arvore_huffman(HUFFMAN *huffman, char *msg);

void criar_codigo(HUFFMAN *huffman);

void codificar(HUFFMAN *huffman, char *msg, char *cod);

int decodificar(HUFFMAN *huffman, char *cod, char *msg);

int codificarHuffmanRunLength(HUFFMAN *huffman, char *msg,char *stringRunLength,int N);

int decodificarHuffmanRunLength(HUFFMAN *huffman, char *stringRunLength, char *blocoDescod, int N, int tamRunlenght);

int tamanhoHuffman(HUFFMAN *huffman, char *bloco, int N);


#endif	/* HUFFMAN_H */

