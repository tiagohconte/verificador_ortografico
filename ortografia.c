/*	Feito por Tiago Henrique Conte	
	Trabalho da disciplina de Programação 2 do BCC UFPR
	Verificador Ortográfico	*/

/*#include <stdlib.h>
#include <stdio.h>*/
/*#include <string.h>*/
#include "dicionario.h"

#define SIZE 50

// Verifica se o char é uma letra
int eh_letra(char c){
	// Verifica se é letra minuscula
	if(c >= 'a' && c <= 'z')
		return 1;
	// Verifica se é letra maiuscula
	else if(c >= 'A' && c <= 'Z')
		return 1;
	// Verifica se é letra acentuada
	else if((c >= -64 && c <= -1))
		return 1;

	return 0;
}

int main(int argc, char const *argv[]){	

	tad_dicio dicio;
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
		while(!eh_letra(c) && !feof(stdin)){
			printf("%c", c);
			c = fgetc(stdin);
		}
		// Lê a palavra
		char palavra[SIZE+1] = {0};
		i = 0;
		while(eh_letra(c) && !feof(stdin)){
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