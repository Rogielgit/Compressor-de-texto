#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preencheT_R(char *vector_T,char *aux_vector_T,int *vector_R, char *string, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{	
		vector_T[i] = aux_vector_T[i] = string[i];
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
void pegaLinhaF(char *string_rotate, char *vector_T, int N) // pega a ultima linha, no caso é a que será codificada
{
	int i;
	string_rotate[0] = vector_T[N-1]; 
	for (i=1; i < N; i++) string_rotate[i] = vector_T[i-1];
}

int main()
{

	int N,i; // para matriz quadrada
	char *vector_T,*aux_vector_T, *string, *string_rotate; // string vai sair depois
	int *vector_R;


	scanf("%d", &N);
	fflush(stdin);
	string = (char*)malloc((N+1)*sizeof(char));
	vector_R = (int*)malloc((N)*sizeof(int));
	vector_T = (char*)malloc((N)*sizeof(char));
	aux_vector_T = (char*)malloc((N)*sizeof(char));
	string_rotate = (char*)malloc((N)*sizeof(char));

	scanf("%s",string);

	preencheT_R(vector_T,aux_vector_T,vector_R,string,N); // N is the name de bloco that need read.
	pegaLinhaF(string_rotate,vector_T,N);
	quickSort(vector_T, aux_vector_T,vector_R,0,N-1,N);

	for (i = 0;i < N; i++)	printf("%c -> %d\n",string_rotate[vector_R[i]], vector_R[i]);
	printf("\n\n");


	/*
	FILE *arq;
	int result,i=0;
	char Linha[101];
	arq = fopen("arquivo.txt", "rb");
	if (arq == NULL)
	{
		printf("Nao foi possivel abrir\n");
		exit(0);
	}

	while (!feof(arq))
  {
	// Lê uma linha (inclusive com o '\n')
      result = fgets(Linha,100,arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
      if (result)  // Se foi possível ler
	  	printf("Linha %d : %s\n",i,Linha);
      	i++;
  }
  

	fclose (arq);*/
  	free(vector_T);
  	free(vector_R);
  	free(string);
  	free(aux_vector_T);
	free (string_rotate);
 
return 0;
}


