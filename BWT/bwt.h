#ifndef BWT_H
#define BWT_H


void preencheT_R(char *vector_T,char *bloco,char *aux_vector_T,int *vector_R,int N);


void trocaPosicao(char *vector_T, int *vector_R, int i, int j);

int partition(char *vector_T, char *aux_vector_T, int *vector_R,int min, int N, int TAM);


void quickSort(char *vector_T, char *aux_vector_T, int *vector_R, int min, int N, int TAM);

void pegaLinhaL(char *string_rotate, char *vector_T, int N); // pega a ultima linha, no caso é a que será codificada


int indxInicioBloco(int *vector_R, int N);


int criavetorK(char *vetor_k, char *vetor_F, int N); 


void preencheVetorC(char *bloco, char *vetor_k, int *vetorFreqK, int *vetorC, int tamK, int N);

void decodifiBWT(char *blocoDescod, char *bloco, char *vetor_F, int *vetorC, int a, int N);


void mergeSort(char *vetor, int posicaoInicio, int posicaoFim); // para descodificar o BWT

void copiaString(char *string1, char *string2, char *bloco, int *vector_R, int N);






#endif /*BWT_H*/