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

	int i=0; 
	char *vector_T,*aux_vector_T,*string_rotate; // string vai sair depois
	int *vector_R, tamanhoFreq, tamRunlenght, tamanho,*vetorFreqK, *vetorC, a;
	int tamHuffman;
	
	char *stringRunLength, *vetor_F;
	char *blocoDescod, *bloco;
	char *vetor_k;

	char *blococofHuff;
  	char decodificado[1000];

  	char saidaCmp[5];
  	int tamBloco, passo1 = 0, passo2 = 0, passo3 = 0;
  	char ch;
	HUFFMAN *huffman;

  	
  	if (strcmp(argv[1],"-i") == 0)
  	{
  		//printf("entrada \n");
  		//printf("%s\n",argv[2]);

  		arq = fopen(argv[2], "r");
  		if (arq == NULL)
		{
			printf("Nao foi possivel abrir\n");
			exit(0);
		}
		
		tratarArgv(argv[6],saidaCmp);
  		tamBloco = atoi(saidaCmp);

  		bloco = (char*)malloc((tamBloco+1)*sizeof(char)); // para calcular a frequencia de letras.
		stringRunLength = (char*)malloc(100*sizeof(char)); // para calcular a frequencia de letras.
		vetor_F = (char*)malloc(tamBloco*sizeof(char));
		vetor_k = (char*)malloc(sizeof(char));
		vetorC = (int*)malloc(tamBloco*sizeof(int));
		blocoDescod = (char*)malloc(tamBloco*sizeof(char)); // para calcular a frequencia de letras.

		while (i < tamBloco)
  		{	
      		ch = getc(arq);      		
      		bloco[i] =ch;
      		i++;
  		}
  		bloco[i] = '\0';
  		//printf("tamBloco %d\n",tamBloco);
  		tratarArgv(argv[5],saidaCmp);
  		if (strcmp(saidaCmp,"true") == 0) // bwt
  		{

  			vector_R = (int*)malloc((tamBloco)*sizeof(int));
			vector_T = (char*)malloc((tamBloco)*sizeof(char));
			aux_vector_T = (char*)malloc((tamBloco)*sizeof(char));
			string_rotate = (char*)malloc((tamBloco)*sizeof(char));

  			preencheT_R(vector_T,bloco,aux_vector_T,vector_R,tamBloco); // N is the name de bloco that need read.
			pegaLinhaL(string_rotate,vector_T,tamBloco);
			quickSort(vector_T, aux_vector_T,vector_R,0,tamBloco-1,tamBloco);

			printf("\nCodificacao BWT\n");
			copiaString(string_rotate,vetor_F,blocoDescod,vector_R, tamBloco);
			for (i = 0;i < tamBloco; i++) printf("%c",blocoDescod[i]);
			printf("\n\n");			
			a = indxInicioBloco(vector_R,tamBloco);
			printf("A = %d\n",a );
			
			passo1 = 1;
			//para descodificar
			/*
			mergeSort(vetor_F,0,tamBloco-1);
			tamanho = criavetorK(vetor_k,vetor_F,tamBloco);
			vetorFreqK = (int*)calloc(tamanho,sizeof(int));
			preencheVetorC(bloco,vetor_k,vetorFreqK,vetorC,tamanho,tamBloco);*/
			
			//BWT
	
			/*printf("BWT descodificada\n");
			decodifiBWT(blocoDescod,bloco,vetor_F,vetorC,a,N);

			for (i = 0; i < tamBloco; i++) printf("%c",blocoDescod[i]);
			printf("\n\n");*/
	

			free(vector_R);
  			free(vector_T);
  			free(aux_vector_T);
			free (string_rotate);
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

		
		//	printf("TA %d\n", tamanhoHuffman(huffman,bloco,tamBloco));
 			for(i =0; i < tamHuffman; i++) printf("%c", blococofHuff[i]); // arrumar
 			printf("\n");






  			//para descodificar
  			/*
  			decodificar(huffman,codificado,decodificado);
  			printf("decodificacao: %s\n", decodificado); // arrumar
			*/



   	//apagar_huffman(&huffman);

  			passo2 = 1;



  		}
  		tratarArgv(argv[8],saidaCmp);
  		if (strcmp(saidaCmp,"true")==0) // runlenght
  		{
  			 /**Run-Length**/
			printf("\n\nUsar no run lenght\n");
			printf("Vetor - TES\n");
			for (i = 0; i < tamBloco; i++) printf("%c",bloco[i]);
			printf("\n\n");
			if (passo1 == 1 && passo2 != 1) 
			{
				tamRunlenght = calculaRunLengthFrequencia(blocoDescod,stringRunLength,tamBloco); //passa a string que queremos codificar(pura,huffman, BWT)
				for (i = 0; i < tamRunlenght; i++) printf("%c",stringRunLength[i]);
			printf("\n\n");
			}
			//arrumar as combinações
			else if (passo2 == 1 && passo1 != 1) // não passou pelo bwt
			{

				printf("Huffman para Run-Length\n");	
				tamRunlenght = codificarHuffmanRunLength(huffman,bloco,stringRunLength,tamBloco);
				printf("tamanho %d\n",tamRunlenght);
				for (i = 0; i < tamRunlenght; i++) printf("%c",stringRunLength[i]);
				printf("\n\n");	
			}

			else if (passo1 != 1 && passo2 != 1)
			{
				tamRunlenght = calculaRunLengthFrequencia(bloco,stringRunLength,tamBloco);
				printf("tamanho %d\n",tamRunlenght);
				for (i = 0; i < tamRunlenght; i++) printf("%c",stringRunLength[i]);
				printf("\n\n");
			} 
			else 
			{

				printf("Huffman para Run-Length\n");	
				tamRunlenght = codificarHuffmanRunLength(huffman,blocoDescod,stringRunLength,tamBloco);
				printf("tamanho %d\n",tamRunlenght);
				for (i = 0; i < tamRunlenght; i++) printf("%c",stringRunLength[i]);
				printf("\n\n");	
			 }
			
				
			//para decodificar
			/*
				decodificarHuffmanRunLength(huffman,stringRunLength,blocoDescod,N, tamRunlenght);
				for (i =0; i<N; i++) printf("%c",blocoDescod[i]);
				printf("\n");*/
					

			passo3 = 1;
			/*			descodificaRunLenght(stringRunLength,blocoDescod,tamRunlenght);
			for (i = 0; i < N; i++) printf("%c",blocoDescod[i]);
			printf("\n\n");*/
		}
  	}
  	
  	if (strcmp(argv[3],"-o") == 0)
  	{

  		arqSaida = fopen(argv[4], "wb+");
  		if (arq == NULL)
		{
			printf("Nao foi possivel abrir\n");
			exit(0);
		}

		if (passo1 == 1 && passo2 != 1 && passo3 != 1) // apenas bwt 
		{
			fprintf(arqSaida, "%d%d\n",tamBloco,a);	
			fprintf(arqSaida, "%s",blocoDescod);
		}
		else if (passo1 != 1 && passo2 == 1 && passo3 != 1) // apenas huffman
		{
			fprintf(arqSaida, "%d%d\n",tamBloco,tamHuffman);	
			fprintf(arqSaida, "%s",blococofHuff);	
		}
		else if (passo1 != 1 && passo2 != 1 && passo3 == 1) // runlenght
		{
			fprintf(arqSaida, "%d%d\n",tamBloco,tamRunlenght);	
			fprintf(arqSaida, "%s",stringRunLength);
		}
		else if (passo1 == 1 && passo2 == 1 && passo3 != 1) // bwt e huffman
		{
			fprintf(arqSaida, "%d%d%d\n",tamBloco,a,tamHuffman);	
			fprintf(arqSaida, "%s",blocoDescod);
		}
		else if (passo1 != 1 && passo2 == 1 && passo3 == 1) // huffman e runlenght
		{
			fprintf(arqSaida, "%d%d\n",tamBloco,tamRunlenght);	
			fprintf(arqSaida, "%s",stringRunLength);
		}
		else // bwt, huffman e  runlenght
		{
		 	fprintf(arqSaida, "%d%d%d\n",tamBloco,a,tamRunlenght);	
			fprintf(arqSaida, "%s",stringRunLength);
		}
	
		



		


  	}
  	
  	

	fclose (arq);
	//fclose(arqSaida);
  	free(bloco);  	
	free(stringRunLength);
	free(vetor_F);
	free(vetor_k);
	free(vetorC);
	free(blocoDescod);
 	

	
return 0;
}


