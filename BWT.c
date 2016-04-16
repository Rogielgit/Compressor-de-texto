//open music


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int sup,inf;

}Elemento; 

typedef struct{
    
    int topo;
    Elemento *p;   

}Pilha;


////////////////


typedef struct
{
	char *string;
}Bloco;

Pilha *Create(int capacidade){

    Pilha *aux;
    aux=(Pilha*)malloc(sizeof(Pilha*)); // aloca uma pilha do tipo Stack
    if (aux==NULL) return NULL;
    else{
        aux->p = (Elemento*)malloc(capacidade*sizeof(Elemento)); // aloca uma pilha do tamanho capacity
        if (aux->p==NULL) return NULL;
        aux->topo=-1; 
        
        return (aux);        
       }
    
return NULL;
}

void push(Pilha *pilha, Elemento *elemento){    

    pilha->topo++;
    pilha->p[pilha->topo].sup=elemento->sup;// arrumar; 
    pilha->p[pilha->topo].inf=elemento->inf;// arrumar; 
}
void pop(Pilha *pilha, Elemento *elemento){    
    
    elemento->inf = pilha->p[pilha->topo].inf;
    elemento->sup = pilha->p[pilha->topo].sup; 
    pilha->topo--;

}
int EstaVazia(Pilha *pilha){
  
    if (pilha->topo==-1) return 1;

return -1;    
}
/*
void particao(Bloco *bloco,int min, int max, int *p){
	int a, i, temp, temp2, j, troca;
	a = vector_T[min]; // a é o elemento cuja posição final é procurada (pivô)
	j = max;
	i = min;
	troca = 0;
	while (i < j){
		if (!troca)
			while (vector_T[i] >= vector_T[j] && i < j)	j--;
		else
			while (vector_T[i] >= vector_T[j] && i < max) i++;
			if (i < j){ //troca x[i] e x[j]
		
				temp2 = vector_R[i];				
				if (vector_T[i] == vector_T[j])
				{
					if (vector_R[j] < vector_R[])
					{
						vector_R[i] = vector_R[j];
						vector_R[j] = temp2;

					}

				}
				else
				{										
					vector_R[i] = vector_R[j];	
					vector_R[j] = temp2;
				}
					vector_R[i] = vector_R[j];	
					vector_R[j] = temp2;
				temp = vector_T[i];
				vector_T[i] = vector_T[j];
				vector_T[j] = temp;
				
				troca = 1-troca;
			}	
	}
	vector_T[j] = a;
	*p = j;
}

void quicksort(char *vector_T, int *vector_R, int n){


int i,j;
Pilha *pilha;
Elemento elemento;
elemento.inf = 0; elemento.sup = n-1;
pilha= Create(n);
push(pilha, &elemento);
while (EstaVazia(pilha)!=1){ // repete enquanto existir algum subvetor não classificado
	pop(pilha,&elemento);
	while(elemento.inf < elemento.sup){ // processa a subvetor seguinte
		particao(vector_T,vector_R, elemento.inf, elemento.sup, &j);// empilha o subvetor maior
		if(j-elemento.inf > elemento.sup-j){ // empilha o subvetor inferior
			i = elemento.sup;
			elemento.sup = j-1;
			push(pilha, &elemento);// processa o subvetor superior
			elemento.inf = j+1; elemento.sup = i;
		}else{ // empilha o subvetor superior
			i = elemento.inf;
			elemento.inf = j+1;
			push(pilha, &elemento);// processa o subvetor inferior
			elemento.inf = i; elemento.sup = j-1;
		}
	}
}
}

*/

void rotateBloco(Bloco *bloco,int N)
{
	int i, j, k;
	for (i = 0; i < N-1; i++)
	{	
		k = N-1;
		for (j = 0; j < N; j++)
		{
			if (j == 0) // coloca o primiero na ultima posição
			{
				bloco[i+1].string[N-1] = bloco[i].string[j];
				//bloco[i+1].string[N] = '\0';				
			}
			else
				bloco[i+1].string[j-1] = bloco[i].string[j];

			
			k--;
		}
	}
}

void Imprime(Bloco *bloco, int N)
{
	int i;
	printf("vector ini:\n");
	
	for (i = 0; i < N; i++)
	{
		printf("%s",bloco[i].string);
		printf("\n");	
	}
	
	
	printf("\n\n");

}


void selection_sort(Bloco *bloco,int* vector_R, int tam) 
{ 
  int i, j, min, temp;
  char *stringTemp;

   stringTemp = (char*)malloc((tam+1)*sizeof(char));

   
  for (i = 0; i < (tam-1); i++) 
   {
    min = i;
    for (j = (i+1); j < tam; j++) {
      if(strcmp(bloco[j].string, bloco[min].string) < 0) 
        min = j;
    }
    if (i != min){

    	strcpy(stringTemp, bloco[i].string);
    	strcpy(bloco[i].string, bloco[min].string);
    	strcpy(bloco[min].string,stringTemp);

    	temp = vector_R[i];
    	vector_R[i] = vector_R[min];
    	vector_R[min]= temp; 
     
    }

  }
  free(stringTemp);
}

void guardaTR(Bloco *bloco, char *vector_T, int *vector_R, char* string_rotate, int N)
{
	int i, j=0;
	string_rotate[j] = bloco[j].string[N-1]; // guarda o ultimo
	j++;
	for(i=0; i< N; i++)
	{
		vector_T[i] = bloco[0].string[i]; // para mapear os caracteres
		vector_R[i] = i; // para sabemos o inicio de cada caracter
		string_rotate[j] = bloco[j-1].string[0];
		j++;
	}
}



int main ()
{

	int N,i; // para matriz quadrada
	Bloco *bloco;
	char *vector_T, *string, *string_rotate; // string vai sair depois
	int *vector_R;


	scanf("%d", &N);
	fflush(stdin);
	string = (char*)malloc((N+1)*sizeof(char));
	vector_R = (int*)malloc((N)*sizeof(int));
	vector_T = (char*)malloc((N)*sizeof(char));
	string_rotate = (char*)malloc((N)*sizeof(char));

//
	bloco = (Bloco*)malloc(N*sizeof(bloco));
	for(i =0; i< N; i++)
	{
		bloco[i].string = (char*)malloc((N+1)*sizeof(char));
	}

	scanf("%s", bloco[0].string);

	
	rotateBloco(bloco, N);
	guardaTR(bloco,vector_T,vector_R,string_rotate,N);
	selection_sort(bloco,vector_R, N);
	Imprime(bloco,N);


	printf("\n\n");
	for (i = 0;i < N; i++)
	{
		printf("%c -> %d\n",vector_T[vector_R[i]], vector_R[i]);
		
		
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

