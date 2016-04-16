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

void particao(char *vector_T, char *aux_vector_T, int *vector_R,int min, int max, int *p){
	int a, i, temp, temp2, j, troca, auxComp;
	a = vector_T[min]; // a é o elemento cuja posição final é procurada (pivô)
	j = max;
	i = min;
	troca = 0;
	while (i < j){
		if (!troca){
			while (vector_T[i] <= vector_T[j] && i < j)
			{
				if (vector_T[i] == vector_T[j]){
					printf("tes\n");
					for (auxComp = 1; auxComp < 11; auxComp++)
					{	

						if(aux_vector_T[vector_R[i] + auxComp] == aux_vector_T[vector_R[j] + auxComp]); //continue if equal
						else if (aux_vector_T[vector_R[i] + auxComp] < aux_vector_T[vector_R[j] + auxComp])
						{
							j--;
							break;
						}
						else  break;
					}
				}
				else j--;
			}
			}	
		else
		{
			while (vector_T[i] <= vector_T[j] && i < max)
				{
					if (vector_T[i] == vector_T[j]){
						printf("tes2\n");
						for (auxComp = 1; auxComp < 11; auxComp++)
						{	
							if(aux_vector_T[vector_R[i] + auxComp] == aux_vector_T[vector_R[j] + auxComp]); //continue if equal
							else if (aux_vector_T[vector_R[i] + auxComp] < aux_vector_T[vector_R[j] + auxComp])
							{
								i++;
								break;
							}
							else break;
						}
					}
					else i++;
				
				}
			} 
			if (i < j){ //troca x[i] e x[j]
		
				temp2 = vector_R[i];				
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

void quicksort(char *vector_T, char *aux_vector_T,int *vector_R, int n){


int i,j;
Pilha *pilha;
Elemento elemento;
elemento.inf = 0; elemento.sup = n-1;
pilha= Create(n);
push(pilha, &elemento);
while (EstaVazia(pilha)!=1){ // repete enquanto existir algum subvetor não classificado
	pop(pilha,&elemento);
	while(elemento.inf < elemento.sup){ // processa a subvetor seguinte
		particao(vector_T,aux_vector_T, vector_R, elemento.inf, elemento.sup, &j);// empilha o subvetor maior
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

void preencheT_R(char *vector_T,char *aux_vector_T,int *vector_R, char *string, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{	
		vector_T[i] = aux_vector_T[i] = string[i];

		vector_R[i] = i;
	}
}


int main ()
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
	quicksort(vector_T,aux_vector_T,vector_R,N);
	//rotateBloco(bloco, N);
	///guardaTR(bloco,vector_T,vector_R,string_rotate,N);
	//selection_sort(bloco,vector_R, N);
	//Imprime(bloco,N);


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


