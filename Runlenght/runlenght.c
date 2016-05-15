
#include <stdio.h>
#include <stdlib.h>

#include "runlenght.h"




int calculaRunLengthFrequencia(char *bloco, char *stringRunLength, int N) // para achar a quantidade de vezes que aparece em um vetor
{

	int i,j=0, k = 0,l;
	int n,  quantRepet = 0;
	char numeroConver[8];	

	
	for (i= 0; i < N-1; i++)
	{
		if(bloco[i] == bloco[i+1]) quantRepet+=1; // vai guardando quant que o caracter aparece em seguida
		else
		{
			quantRepet+=1;
			n = sprintf(numeroConver, "%d", quantRepet); // função para converte int para string				
			for (l = 0; l < n; l++)
			{
		//		stringRunLength = (char*)realloc(stringRunLength,(k+3)*sizeof(char));		
				stringRunLength[k] = numeroConver[l];
				k++;
			}
			stringRunLength[k] = '#'; // para identificação
			quantRepet = 0;
			k++; // para controlar o preenchimento na stringRunLength
			stringRunLength[k] = bloco[i];
			k++; 
		}			
	}
	quantRepet+=1;
	n = sprintf(numeroConver, "%d", quantRepet); // função para converte int para string				
	for (l = 0; l < n; l++)
	{
		//stringRunLength = (char*)realloc(stringRunLength,(k+3)*sizeof(char));		
		stringRunLength[k] = numeroConver[l];
		k++;
	}
	stringRunLength[k] = '#'; // para identificação
	k++; // para controlar o preenchimento na stringRunLength
	stringRunLength[k] = bloco[i];
	k++; 
	

return k;
}

/*tentar pensar em uma maneira mais eficiente*/
void descodificaRunLenght(char *stringRunLength, char *blocoDescod, int tamRunlenght)
{
	int i = 0, j, k = 0 ,auxcmp, cont = 0, tamString = 0;
	char stringConver[8];

	
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
		for (j = 0; j < auxcmp; j++)
		{
			blocoDescod[cont] = stringRunLength[i];
			cont++;
		}
		i++; //para começar a pegar os numeros
		
	} 
}
