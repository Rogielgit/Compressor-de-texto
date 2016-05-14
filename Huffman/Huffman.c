/*
* Codigo baseado na Aula do Paulovich
*
*/

#include <stdlib.h>
#include <stdio.h>

#include "Huffman.h"
#include "HeapEstatica.h"
#include "ArvoreBinaria.h"

#define TAM 500

//Estrutura que armazenará a árvore e uma matriz para o código.
struct huffman{

  ARVORE_BINARIA *arvore;
  char codigo[TAM][TAM];
};

//Criará a estrutura de Huffman.
HUFFMAN *criar_huffman()
{

  HUFFMAN *huffman = (HUFFMAN*)malloc(sizeof(HUFFMAN));
  int i;
  if (huffman != NULL){

    for (i = 0; i < TAM; i++)  huffman->codigo[i][0] = '\0';
    huffman->arvore = NULL;
  }
  return huffman;
}

void criar_arvore_huffman(HUFFMAN *huffman, char *msg) {

  int i, freq[TAM];
  for (i = 0; i < TAM; i++) freq[i] = 0;
    /*trocar por malloc*/
  for (i = 0; msg[i] != '\0'; i++) freq[(int) msg[i]]++; // cria a frequencia

  HEAP_ESTATICA *heap = criar_heap();

  for (i = 0; i < TAM; i++)
  {
    if (freq[i] > 0){

      NO *pno = (NO *) malloc(sizeof(NO));
      pno->simbolo = i;
      pno->frequencia = freq[i];
      pno->filhodir = NULL;
      pno->filhoesq = NULL;
      inserir_heap(heap, pno);
    }
  }

  while (tamanho_heap(heap) > 1) {
    NO *pno = (NO *) malloc(sizeof (NO));
    pno->simbolo = '#';
    pno->filhoesq = remover_heap(heap);
    pno->filhodir = remover_heap(heap);
    pno->frequencia = pno->filhoesq->frequencia + pno->filhodir->frequencia;
    inserir_heap(heap, pno);
  }

  huffman->arvore = criar_arvore();
  criar_raiz(huffman->arvore, remover_heap(heap));
  apagar_heap(&heap);
}

void criar_codigo_aux(HUFFMAN *huffman, NO *no, char *cod, int fim) {
  if (no != NULL) {
    if (no->filhoesq == NULL && no->filhodir == NULL)
    {
      int i;
      for (i = 0; i <= fim; i++)  huffman->codigo[(int) no->simbolo][i] = cod[i];
      huffman->codigo[(int) no->simbolo][fim + 1] = '\0';

    }else {
      if (no->filhoesq != NULL) {
        fim++;
        cod[fim] = '0';
        criar_codigo_aux(huffman, no->filhoesq, cod, fim);
        fim--;
      }

      if (no->filhodir != NULL) {
        fim++;
        cod[fim] = '1';
        criar_codigo_aux(huffman, no->filhodir, cod, fim);
        fim--;
      }
    }
  }
}

void criar_codigo(HUFFMAN *huffman){

  char codigo[TAM];
  criar_codigo_aux(huffman, huffman->arvore->raiz, codigo, -1);
}

void codificar(HUFFMAN *huffman, char *msg, char *cod, int N)
{
 
  int i, j, cod_fim;
  cod_fim = -1;

  for (i = 0; i < N; i++)
  {
    char *pcod = huffman->codigo[(int)msg[i]];
    for (j = 0; pcod[j] != '\0'; j++)
    {
      cod_fim++;
      cod[cod_fim] = pcod[j];
    }

  }
  cod[cod_fim + 1] = '\0';
}

int tamanhoHuffman(HUFFMAN *huffman, char *bloco, int N)
{
  int tam = 0, i,j;
  for (i = 0; i < N; i++)
  {
    char *pcod = huffman->codigo[(int)bloco[i]];
    for (j = 0; pcod[j] != '\0'; j++) tam++;
  }
 

  return tam;
}

int decodificar(HUFFMAN *huffman, char *cod, char *msg){

  int i, decod_fim;
  decod_fim = -1;

  NO *pno = huffman->arvore->raiz;

  for (i = 0; cod[i] != '\0'; i++)
  {
    if (cod[i] == '0') pno = pno->filhoesq;
    else if (cod[i] == '1') pno = pno->filhodir;
    else return 0;
    
    if (pno->filhoesq == NULL && pno->filhodir == NULL) {
      decod_fim++;
      msg[decod_fim] = pno->simbolo;
      pno = huffman->arvore->raiz;
    }
  }

  msg[decod_fim + 1] = '\0';
  return 1;
}

int codificarHuffmanRunLength(HUFFMAN *huffman, char *bloco, char *stringRunLength,int N)
{
 
  int p, f, cod_fim;
  int i,j=0, k = 0,l;
  int n,  quantRepet = 0; 
  char *pcod;
  char numeroConver[8];

  
    for (i= 0; i < N-1; i++)
    {
      

      if(bloco[i] == bloco[i+1])  quantRepet+=1; // vai guardando quant que o caracter aparece em seguida
      else
      { 
        pcod = huffman->codigo[(int)bloco[i]];
        quantRepet+=1;
        n = sprintf(numeroConver,"%d",quantRepet); // função para converte int para string        
        for (l = 0; l < n; l++)
        {
          
          stringRunLength = (char*)realloc(stringRunLength,(k+1)*sizeof(char));   
          stringRunLength[k] = numeroConver[l];          
          k++;
        }
        
        stringRunLength = (char*)realloc(stringRunLength,(k+1)*sizeof(char));   
        stringRunLength[k] = '#'; // para identificação
        k++; // para controlar o preenchimento na stringRunLength
        quantRepet = 0;
        for (f = 0; pcod[f]!='\0'; f++)
        {         
          stringRunLength = (char*)realloc(stringRunLength,(k+1)*sizeof(char));   
          stringRunLength[k] = pcod[f];        
          k++;      
        }
      }
     }
    pcod = huffman->codigo[(int)bloco[i]];
    quantRepet+=1;
    n = sprintf(numeroConver, "%d", quantRepet); // função para converte int para string        
    for (l = 0; l < n; l++)
    {
      stringRunLength = (char*)realloc(stringRunLength,(k+1)*sizeof(char));   
      stringRunLength[k] = numeroConver[l];
      k++;
    }
    stringRunLength = (char*)realloc(stringRunLength,(k+1)*sizeof(char));   
    stringRunLength[k] = '#'; // para identificação
    k++; // para controlar o preenchimento na stringRunLength
    for (f = 0; pcod[f]!='\0'; f++)
    {         
      stringRunLength = (char*)realloc(stringRunLength,(k+1)*sizeof(char));   
      stringRunLength[k] = pcod[f];        
      k++;                 
    }
  
  
    
return k;
}

int decodificarHuffmanRunLength(HUFFMAN *huffman, char *stringRunLength, char *blocoDescod,int N, int tamRunlenght)
{

  int flag =0, guardaI;
  int decod_fim = -1;
  int i= 0, j, k = 0 ,auxcmp,tamString = 0;
  char stringConver[8];


  NO *pno = huffman->arvore->raiz;

     while (i < tamRunlenght)
    { 
      for (k=0 ; stringRunLength[i] != '#'; k++)
      {
        stringConver[k] = stringRunLength[i];
        i++;  
      } 
    
      stringConver[k] = '\0';           
      auxcmp = atoi(stringConver); // converte para int
      i++; // para pegar o caractere
      guardaI = i; // guarda o inicio depois do #
      for (j = 0; j < auxcmp; j++)
      {       
        flag = 0;
        i = guardaI; // caso tenha mais de um caracter
        while (flag == 0)
        {
          if (stringRunLength[i] == '0') pno = pno->filhoesq;
          else if (stringRunLength[i] == '1') pno = pno->filhodir;
          else return 0;
          i++;
      
          if (pno->filhoesq == NULL && pno->filhodir == NULL) {
            decod_fim++;
            blocoDescod[decod_fim] = pno->simbolo;
            pno = huffman->arvore->raiz;
            flag=1;
          }
        }
      }
      
  }

 // msg[decod_fim + 1] = '\0';
  return 1;




  
 
}

void apagar_huffman(HUFFMAN **huffman) {
  apagar_arvore(&((*huffman)->arvore));
  free(*huffman);
  *huffman = NULL;
}


