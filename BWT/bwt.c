

#include "bwt.h"
#include <stdlib.h>



void preencheT_R(char *vector_T,char *bloco, char *aux_vector_T,int *vector_R, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{	
		vector_T[i] = aux_vector_T[i] = bloco[i];
		vector_R[i] = i; // vetor de indices
	}
}

void trocaPosicao(char *vector_T, int *vector_R, int i, int j)
{
	int temp;

	temp = vector_T[j];
	vector_T[j] = vector_T[i];
	vector_T[i] = temp;

	temp = vector_R[j];
	vector_R[j] = vector_R[i];
	vector_R[i] = temp;
}

int partition(char *vector_T, char *aux_vector_T, int *vector_R,int min, int N, int TAM)
{
	
	int x, xR,i;

	int j = min - 1;
	int somaI,somaX;

	x = vector_T[N];
	xR = vector_R[N];

	for (i = min; i < N; i++) {

		if (x >= vector_T[i])
		{			
			if (x == vector_T[i]){ 
				somaX = xR + 1;
				somaI = vector_R[i] + 1 ;

				while (1)  // para tratar os caso de desempate, comparando cada caracter até ser difirente
				{	
					if (somaX >= TAM) somaX = 0;	 // caso passe do tamanho do vetor, volta para o inicio
					if (somaI >= TAM) somaI = 0;					

					if(aux_vector_T[somaX] == aux_vector_T[somaI]); // caso seja igual continua a comparar												
					else if (aux_vector_T[somaX] > aux_vector_T[somaI])
					{
						j = j + 1;
						trocaPosicao(vector_T,vector_R, i,j); // para trocar as posições dos vetores
						break;
					}
					else break;
					
					somaX +=1;
					somaI +=1;
					 
				}			
			}
			else
			{
				j = j + 1;
				trocaPosicao(vector_T,vector_R, i,j);
			} 
		}
	}

	vector_T[N] = vector_T[j + 1];
	vector_T[j + 1] = x;

	vector_R[N] = vector_R[j + 1];
	vector_R[j + 1] = xR;
	return (j + 1);
}

void quickSort(char *vector_T, char *aux_vector_T, int *vector_R, int min, int N, int TAM)
{ 
	int q;
	
	if (min < N) 
	{
		q = partition(vector_T,aux_vector_T,vector_R, min,N, TAM);
		quickSort(vector_T,aux_vector_T,vector_R,min, q-1, TAM);
		quickSort(vector_T,aux_vector_T, vector_R, q+1, N, TAM);
	}
}
void pegaLinhaL(char *string_rotate, char *vector_T, int N) // pega a ultima linha, no caso é a que será codificada
{
	int i;
	string_rotate[0] = vector_T[N-1]; 
	for (i=1; i < N; i++) string_rotate[i] = vector_T[i-1];
}
int indxInicioBloco(int *vector_R, int N)
{
	int i,a;
	for(i = 0; i < N; i++)
	{
		if (vector_R[i] == 0)
		{
			a = i;
			i = N; // para sair	
		} 

	}
	return a;
}



int criavetorK(char *vetor_k, char *vetor_F, int N) 
{	
	int i,j=0;

	for (i = 0; i< N-1; i++)
	{	
		if (vetor_F[i] == vetor_F[i+1]);
		else
		{	
			vetor_k = (char*)realloc(vetor_k,(j+1)*sizeof(char));
			
			vetor_k[j] = vetor_F[i];
			
			j++;
		}
		
	}
	vetor_k = (char*)realloc(vetor_k,(j+1)*sizeof(char));
	vetor_k[j] = vetor_F[i];
	j++;


 return j;
}

void preencheVetorC(char *bloco, char *vetor_k, int *vetorFreqK, int *vetorC, int tamK, int N)
{

	int i,j;//parei aqui
	for (i = 0; i< N; i++)
	{
		for (j = 0; j < tamK; j++)
		{
			if (vetor_k[j] == bloco[i])
			{				
				vetorC[i]= vetorFreqK[j];
				vetorFreqK[j]+=1;
			}
		}
	}
}

void decodifiBWT(char *blocoDescod, char *bloco, char *vetor_F, int *vetorC, int a, int N)
{

	int i, j, k,cont=-1;
	char c;

	for (i = 0; i < N; i++)
	{	
		c = vetor_F[a];
		for (j = 0; j <= a; j++)
		{
			if (c == vetor_F[j]) cont++;
		}
		blocoDescod[i] = c; // ja quarda o caracter descodificado
		for (k = 0 ; k < N; k++)
		{
			if (bloco[k] == c && vetorC[k] == cont) // verifica a ocorrencia
			{
				a = k;
				k = N;
			}
		}
		cont=-1;
	}
}


// para ordenar o frequencia 
/* retirado de https://pt.wikipedia.org/wiki/Merge_sort*/

void mergeSort(char *vetor, int posicaoInicio, int posicaoFim) // para descodificar o BWT
{ 
   
    int i, j, k, metadeTamanho;
    int *vetorTemp;
    if(posicaoInicio == posicaoFim) return;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim)/2;
    mergeSort(vetor, posicaoInicio, metadeTamanho);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim);

    // intercalacao no vetor temporario t
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (int*)malloc(sizeof(int)*(posicaoFim - posicaoInicio + 1));

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
        if (i == metadeTamanho + 1 ) { // i passou do final da primeira metade, pegar v[j]
            vetorTemp[k] = vetor[j];
            vetorTemp[k] = vetor[j];
            j++;
            k++;
        } 
        else {
            if (j == posicaoFim + 1) { // j passou do final da segunda metade, pegar v[i]
                vetorTemp[k] = vetor[i];
                vetorTemp[k] = vetor[i];
                i++;
                k++;
            } 
            else {
                if (vetor[i] < vetor[j]) { 
                    vetorTemp[k] = vetor[i];
                    vetorTemp[k] = vetor[i];
                    i++;
                    k++;
                } 
                else { 
                    vetorTemp[k] = vetor[j];
                    vetorTemp[k] = vetor[j];
                    j++;
                    k++;
                }
            }
        }

    }
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++) {
        vetor[i] = vetorTemp[i - posicaoInicio];
        vetor[i] = vetorTemp[i - posicaoInicio];
    }
    free(vetorTemp);
}
/*
*
* Fazer uma função de compiar string 
*
*/

void copiaString(char *string1, char *string2, char *bloco, int *vector_R, int N)
{	
	int i;
	for (i = 0; i < N; i++) bloco[i] = string2[i] = string1[vector_R[i]];
	
}
