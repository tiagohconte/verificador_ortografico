/*	Feito por Tiago Henrique Conte	
	Trabalho da disciplina de Programação 2 do BCC UFPR
	Verificador Ortográfico	
	Implementação de funções da biblioteca dicionário	*/

#include "dicionario.h"

/* Função para carregar o dicionário na memória */
int carrega_dicionario(tad_dicio *dicio){
	// Abre arquivo do dicionário
	FILE *arq_dicio;

	arq_dicio = fopen(DIR, "r");
	if(!arq_dicio){
		fprintf(stderr, "Erro ao abrir arquivo dicionário.");
		return 0;
	}

	char c;
	dicio->linhas = 0;
	dicio->palavras = 0;
	// Conta o número de linhas no arquivo dicionário
	while(!feof(arq_dicio)){
		c = fgetc(arq_dicio);
		if(c == '\n')
			(dicio->linhas)++;
	}

	// Aloca espaço na memória para as palavras
	dicio->palavras = malloc(dicio->linhas * sizeof(dicio->palavras));
	if(dicio->palavras == NULL){
		fprintf(stderr, "Erro ao alocar dicionário.\n");
		return 0;
	}

	// Lê o arquivo dicionário e guarda na memória
	rewind(arq_dicio);
	char str[SIZE+1];
	int i = 0;
	while(!feof(arq_dicio)){
		fgets(str, SIZE, arq_dicio);
		// Aloca espaço para a palavra
		dicio->palavras[i] = malloc(strlen(str) * sizeof(char));
		if(dicio->palavras[i] == NULL){
			fprintf(stderr, "Erro ao alocar palavra.\n");
			return 0;
		}
		str[strlen(str)-1] = '\0';
		// Transforma as letras maiusculas em minusculas
		minuscula(str);
		strcpy(dicio->palavras[i], str);		
	}
	/* 	Ao colocar em minusculas o dicionario ficou desordenado
		Portanto é feita a reoordenação das palavras */
	qsort(dicio->palavras, dicio->linhas, sizeof(char*), cmpfunc);

	fclose(arq_dicio);	
	return 1;
}

// Libera espaço da memória
void descarrega_dicionario(tad_dicio *dicio){
	int i;

	for(i = 0; i < dicio->linhas; i++)
		free(dicio->palavras[i]);
	free(dicio->palavras);

	dicio->palavras = NULL;
	dicio = NULL;
}

// Função de comparação para o sort
int cmpfunc(const void * a, const void * b){
   return *(char *)a - *(char *)b; 
}

// Transforma uma string em totalmente minuscula
void minuscula(char *str){
	int i = 0;

	while(str[i]){
		if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= -64 && str[i] <= -35))
			str[i] += 32;
		i++;
	}
}