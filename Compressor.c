#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Huffman/Huffman.h"
#include "Huffman/ArvoreBinaria.h"
#include "Huffman/HeapEstatica.h"

#include "Runlenght/runlenght.h"
#include "BWT/bwt.h"


void fflush_in(){// função para limpar o teclado para usar gets e puts
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

void tratarArgv(char *argv, char *saidaCmp)
{
	int i, j=0, flag = 0;
	for (i = 0; argv[i] != '\0'; i++)
	{
		if (argv[i] == '=' || flag == 1)
		{	
			flag = 1;
			saidaCmp[j] = argv[i+1];
			j++;
		}
	}
}


int main(int argc, char *argv[])
{


	FILE *arq, *arqSaida;

	int i=0,j = 0, flag = 0, flag2 = 0; 
	char *vector_T,*aux_vector_T,*string_rotate; // string vai sair depois
	int *vector_R, tamanhoFreq, tamRunlenght, tamanho,*vetorFreqK, *vetorC, a;
	int tamHuffman;
	
	char *stringRunLength, *vetor_F;
	char *blocoDescod, *bloco;
	char *vetor_k;

	char *blococofHuff;
  	char decodificado[1000];

  	char saidaCmp[5];
  	int tamBloco, tamBlocoOri, passo1 = 0, passo2 = 0, passo3 = 0;
  	char ch;
	HUFFMAN *huffman;

  	
  	if (strcmp(argv[1],"-i") == 0)
  	{
  		
  		arq = fopen(argv[2], "r");
  		if (arq == NULL)
		{
			printf("Nao foi possivel abrir\n");
			exit(0);
		}
		
		tratarArgv(argv[6],saidaCmp);
  		tamBlocoOri = tamBloco = atoi(saidaCmp);

  		bloco = (char*)malloc((tamBloco+1)*sizeof(char)); // para calcular a frequencia de letras.
		stringRunLength = (char*)malloc(sizeof(char)); // para calcular a frequencia de letras.
		blocoDescod = (char*)malloc(tamBloco*sizeof(char)); // para calcular a frequencia de letras.

		ch = getc(arq);
		while (ch != EOF)
		{ 
			while (ch != EOF && j < tamBloco)
			{	
		  		bloco[j] = ch;
		  		ch = getc(arq);      		
		  		j++;
			}
			bloco[j] = '\0';
			if (j < tamBloco) tamBloco = j-1;
			j=0;
			tratarArgv(argv[5],saidaCmp);
			if (strcmp(saidaCmp,"true") == 0) // bwt
			{

				vector_R = (int*)malloc((tamBloco)*sizeof(int));
				vector_T = (char*)malloc((tamBloco)*sizeof(char));
				aux_vector_T = (char*)malloc((tamBloco)*sizeof(char));
				string_rotate = (char*)malloc((tamBloco)*sizeof(char));
				vetor_F = (char*)malloc(tamBloco*sizeof(char));
				vetor_k = (char*)malloc(sizeof(char));
				vetorC = (int*)malloc(tamBloco*sizeof(int));

				preencheT_R(vector_T,bloco,aux_vector_T,vector_R,tamBloco); // N is the name de bloco that need read.
				pegaLinhaL(string_rotate,vector_T,tamBloco);
				quickSort(vector_T, aux_vector_T,vector_R,0,tamBloco-1,tamBloco);

				copiaString(string_rotate,vetor_F,blocoDescod,vector_R, tamBloco);
				a = indxInicioBloco(vector_R,tamBloco);

				
				passo1 = 1;
				//para descodificar BWT
				/*
				mergeSort(vetor_F,0,tamBloco-1);
				tamanho = criavetorK(vetor_k,vetor_F,tamBloco);
				vetorFreqK = (int*)calloc(tamanho,sizeof(int));
				preencheVetorC(bloco,vetor_k,vetorFreqK,vetorC,tamanho,tamBloco);	
				decodifiBWT(blocoDescod,bloco,vetor_F,vetorC,a,N);

				*/

				free(vector_R);
				free(vector_T);
				free(aux_vector_T);
				free (string_rotate);
				free (vetor_F);
				free(vetor_k);
				free(vetorC);

				} 	
				
				tratarArgv(argv[7],saidaCmp);
				if (strcmp(saidaCmp,"true")==0) // huffman
				{
					huffman = criar_huffman();
					criar_arvore_huffman(huffman,bloco); 
					criar_codigo(huffman);
					tamHuffman = tamanhoHuffman(huffman,bloco,tamBloco);
		   			blococofHuff = (char*)malloc((tamHuffman)*sizeof(char));

					if(passo1 == 1)	codificar(huffman,blocoDescod,blococofHuff);
					else codificar(huffman,bloco,blococofHuff);
	


					//para descodificar
					/*
					decodificar(huffman,codificado,decodificado);
					printf("decodificacao: %s\n", decodificado); 
					apagar_huffman(&huffman);
					*/


					passo2 = 1;


				}
				tratarArgv(argv[8],saidaCmp);
				if (strcmp(saidaCmp,"true")==0) // runlenght
				{
					 /**Run-Length**/
					
					if (passo1 == 1 && passo2 != 1) 
					{
						tamRunlenght = calculaRunLengthFrequencia(blocoDescod,stringRunLength,tamBloco);
					
					}				
					else if (passo2 == 1 && passo1 != 1) // não passou pelo bwt
					{
						tamRunlenght = codificarHuffmanRunLength(huffman,bloco,stringRunLength,tamBloco);
					}

					else if (passo1 != 1 && passo2 != 1)
					{
						tamRunlenght = calculaRunLengthFrequencia(bloco,stringRunLength,tamBloco);
			
					} 
					else 
					{
						tamRunlenght = codificarHuffmanRunLength(huffman,blocoDescod,stringRunLength,tamBloco);
							
				 	}				
					
				//para decodificar
				/*
					decodificarHuffmanRunLength(huffman,stringRunLength,blocoDescod,N, tamRunlenght);
					for (i =0; i<N; i++) printf("%c",blocoDescod[i]);
					printf("\n");*/
						

				passo3 = 1;
				// quando não for usando o huffman
				/*descodificaRunLenght(stringRunLength,blocoDescod,tamRunlenght);*/
			
			}  	

  		if (flag == 0)
  		{
  			arqSaida = fopen(argv[4], "wb+");
  			flag =1; // para abrir o arquivo somente uma vez	
  		} 

  		if (arqSaida == NULL)
		{
			printf("Nao foi possivel abrir\n");
			exit(0);
		}

		if (passo1 == 1 && passo2 != 1 && passo3 != 1) // apenas bwt 
		{
			/*write(&tamBloco,sizeof(int),1,arqSaida);
			fwrite(&a,sizeof(int),1,arqSaida);
			fwrite(blocoDescod,tamBloco,1,arqSaida);*/
			
			if (tamBloco != tamBlocoOri) // chegou no EOF
			{
				fprintf(arqSaida, "%d%d",tamBloco,a);	
				fprintf(arqSaida, "%s",blocoDescod);	
			}
			else
			{
				if (flag2 == 0)
				{
					fprintf(arqSaida, "%d",tamBloco); // para salva somente uma vez o tambloco	
					flag2 = 1;	
				} 
				fprintf(arqSaida, "%d",a);	
				fprintf(arqSaida, "%s",blocoDescod);
			}
		}
		else if (passo1 != 1 && passo2 == 1 && passo3 != 1) // apenas huffman
		{
			
			if (tamBloco != tamBlocoOri) // chegou no EOF
			{
				fprintf(arqSaida, "%d%d",tamBloco,tamHuffman);	
				fprintf(arqSaida, "%s",blococofHuff);	
			}
			else
			{
				if (flag2 == 0)
				{
					fprintf(arqSaida, "%d%d",tamBloco,tamHuffman);	
					flag2 = 1;	
				} 
				fprintf(arqSaida, "%s",blococofHuff);	
			}

		}
		else if (passo1 != 1 && passo2 != 1 && passo3 == 1) // runlenght
		{
			
			if (tamBloco != tamBlocoOri) // chegou no EOF
			{
				fprintf(arqSaida, "%d%d",tamBloco,tamRunlenght);	
				fprintf(arqSaida, "%s",stringRunLength);
			}
			else
			{
				if (flag2 == 0)
				{
					fprintf(arqSaida, "%d%d",tamBloco,tamRunlenght);	
					flag2 = 1;	
				} 
				fprintf(arqSaida, "%s",stringRunLength);	
			}
		}
		else if (passo1 == 1 && passo2 == 1 && passo3 != 1) // bwt e huffman
		{


			if (tamBloco != tamBlocoOri) // chegou no EOF
			{			
				fprintf(arqSaida, "%d%d%d",tamBloco,a,tamHuffman);	
				fprintf(arqSaida, "%s",blococofHuff);
			}
			else
			{
				if (flag2 == 0)
				{
					fprintf(arqSaida, "%d%d%d",tamBloco,a,tamHuffman);			
					flag2 = 1;	
				} 
				fprintf(arqSaida, "%d",a);
				fprintf(arqSaida, "%s",blococofHuff);	
			}
			//free(blococofHuff);
		}
		else if (passo1 != 1 && passo2 == 1 && passo3 == 1) // huffman e runlenght
		{
			if (tamBloco != tamBlocoOri) // chegou no EOF
			{			
				fprintf(arqSaida, "%d%d",tamBloco,tamRunlenght);	
				fprintf(arqSaida, "%s",stringRunLength);
			}
			else
			{
				if (flag2 == 0)
				{
					fprintf(arqSaida, "%d%d",tamBloco,tamRunlenght);			
					flag2 = 1;	
				} 
				fprintf(arqSaida, "%s",stringRunLength);	
			}	
		}
		else // bwt, huffman e  runlenght
		{
			if (tamBloco != tamBlocoOri) // chegou no EOF
			{			
				fprintf(arqSaida, "%d%d%d",tamBloco,a,tamRunlenght);	
				fprintf(arqSaida, "%s",stringRunLength);
			}
			else
			{
				if (flag2 == 0)
				{
					fprintf(arqSaida, "%d%d%d",tamBloco,a,tamRunlenght);			
					flag2 = 1;	
				} 
				fprintf(arqSaida, "%s%d",stringRunLength,a);	
			}	
		}	
	  }
  	} 	 	

	fclose (arq);
	fclose(arqSaida);
  	free(bloco);  	
	free(stringRunLength);
	free(blocoDescod);
 	
	
return 0;
}



