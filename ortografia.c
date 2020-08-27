/*	GRR20190374 Tiago Henrique Conte
	Feito por Tiago Henrique Conte	
	Trabalho da disciplina de Programa��o 2 do BCC UFPR
	Verificador Ortogr�fico	*/

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dicionario.h"

#define SIZE 50

// Declara��o de vari�vel global do tipo dicion�rio
tad_dicio dicio;

int main(){

	setlocale(LC_CTYPE, "pt_BR.iso88591");
	
	// Armazenamento do dicion�rio na mem�ria
	if(!carrega_dicionario(&dicio)){
		printf("Erro ao carregar dicion�rio.\nParando programa...\n");
		return 0;
	}

	char c;
	int i;

	c = fgetc(stdin);

	while(!feof(stdin)){
		// Anda at� encontrar uma letra
		while(!isalpha(c) && !feof(stdin)){
			printf("%c", c);
			c = fgetc(stdin);
		}
		// L� a palavra
		char palavra[SIZE+1] = {0};
		i = 0;
		while(isalpha(c) && !feof(stdin)){
			palavra[i] = c;
			c = fgetc(stdin);
			i++;
		}

		// Busca da palavra no dicion�rio
		if(!feof(stdin)){
			// Copia a palavra com todos os caracteres minusculos
			char copia[strlen(palavra)];
			strcpy(copia, palavra);
			minuscula(copia);

			if(busca_dicio(&dicio, copia))
				printf("%s", palavra);
			else 
				printf("[%s]", palavra);
		}
	}

	descarrega_dicionario(&dicio);

	return 0;
}