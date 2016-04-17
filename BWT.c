#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preencheT_R(char *vector_T,char *aux_vector_T,int *vector_R, char *string, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{	
		vector_T[i] = aux_vector_T[i] = string[i];

		vector_R[i] = i;
	}
}


void selectionSort(char *vector_T, char *aux_vector_T, int *vector_R, int N) {

	int i, j, minIndex, tmp;    
	int temp2,auxCompI, auxCompJ,somaI,somaJ;

	for (i = 0; i < N-1; i++) {

		minIndex = i;
		for (j = i + 1; j < N; j++){
			auxCompI = auxCompJ = 0;
			if (vector_T[j] <= vector_T[minIndex]){
				if (vector_T[j] == vector_T[minIndex]){
					somaI = vector_R[j] + auxCompI;
					somaJ = vector_R[minIndex] + auxCompJ;					

					while (auxCompI < N-1 || auxCompJ < N-1)
					{	
						if (somaI > N)
						{	
							somaI = 0;
							auxCompI = 0;
							somaJ = vector_R[minIndex] + auxCompJ +1;

						}
						if (somaJ > N)
						{
							somaJ = 0 ;
							auxCompJ=0;
							somaI = vector_R[j] + auxCompI+1;

						}
						if(aux_vector_T[somaI] == aux_vector_T[somaJ])
						{

						} //continue if equal
						else if (aux_vector_T[somaI] < aux_vector_T[somaJ])
						{

							minIndex = j;
							break;
						}
						else break;
						
						auxCompI++;
						auxCompJ++;
						somaI = somaI + auxCompI;
						somaJ = somaJ + auxCompJ;
						 
						}
				
					}else minIndex = j;
					
				}

			} 
			if (minIndex != i) 
			{

				tmp = vector_T[i];
				vector_T[i] = vector_T[minIndex];
				vector_T[minIndex] = tmp;

				temp2 = vector_R[i];
				vector_R[i] = vector_R[minIndex];
				vector_R[minIndex] = temp2;



			}
		}
}

void pegaLinhaF(char *string_rotate, char *vector_T, int N)
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
	selectionSort(vector_T, aux_vector_T,vector_R,N);
	


	printf("\n\n");
	for (i = 0; i < N; i++)
	{
		printf("%c -> %d\n",vector_T[i], vector_R[i]);
		
		
	}
	printf("\n\n");
	for (i = 0;i < N; i++)
	{
		printf("%c -> %d\n",string_rotate[vector_R[i]], vector_R[i]);
		
		
	}
	printf("\n\n");

	free(string);

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
return 0;
}


