/*	GRR20190374 Tiago Henrique Conte
	Feito por Tiago Henrique Conte	
	Trabalho da disciplina de Programação 2 do BCC UFPR
	Verificador Ortográfico	*/

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dicionario.h"

#define SIZE 50

// Declaração de variável global do tipo dicionário
tad_dicio dicio;

int main(){

	setlocale(LC_CTYPE, "pt_BR.iso88591");
	
	// Armazenamento do dicionário na memória
	if(!carrega_dicionario(&dicio)){
		printf("Erro ao carregar dicionário.\nParando programa...\n");
		return 0;
	}

	char c;
	int i;

	c = fgetc(stdin);

	while(!feof(stdin)){
		// Anda até encontrar uma letra
		while(!isalpha(c) && !feof(stdin)){
			printf("%c", c);
			c = fgetc(stdin);
		}
		// Lê a palavra
		char palavra[SIZE+1] = {0};
		i = 0;
		while(isalpha(c) && !feof(stdin)){
			palavra[i] = c;
			c = fgetc(stdin);
			i++;
		}

		// Busca da palavra no dicionário
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