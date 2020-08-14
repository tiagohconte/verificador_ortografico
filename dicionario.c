/*	Feito por Tiago Henrique Conte	
	Trabalho da disciplina de Programação 2 do BCC UFPR
	Verificador Ortográfico	
	Implementação de funções da biblioteca dicionário	*/

#include "dicionario.h"
// Define o quanto de memória será alocado por operação de aloc
#define VALOR_ALOC 50000

/* Função para carregar o dicionário na memória */
int carrega_dicionario(tad_dicio *dicio){
	// Abre arquivo do dicionário
	FILE *arq_dicio;
	int num_aloc = 1;		// Registra o número de alocações feitas	

	dicio->linhas = 0;
	dicio->palavras = NULL;
	
	// Alocação de espaço inicial na memória
	dicio->palavras = realloc(dicio->palavras, (num_aloc * VALOR_ALOC) * sizeof(dicio->palavras));
	if(dicio->palavras == NULL){
		fprintf(stderr, "Erro na alocação inicial do dicionário.\n");
		return 0;
	}

	// Lê o arquivo dicionário e guarda na memória
	arq_dicio = fopen(DIR, "r");
	if(!arq_dicio){
		fprintf(stderr, "Erro ao abrir arquivo dicionário.");
		return 0;
	}

	char str[SIZE+1];
	while(!feof(arq_dicio)){
		fgets(str, SIZE, arq_dicio);
		// Aloca espaço para a palavra
		if(dicio->linhas > (num_aloc * VALOR_ALOC)){
			num_aloc++;
			dicio->palavras = realloc(dicio->palavras, (num_aloc * VALOR_ALOC) * sizeof(dicio->palavras));
			printf("Linhas: %d, num_aloc: %d\n", dicio->linhas, num_aloc);
		}
		dicio->palavras[dicio->linhas] = malloc(strlen(str) * sizeof(char));
		if(dicio->palavras[dicio->linhas] == NULL){
			fprintf(stderr, "Erro ao alocar palavra.\n");
			return 0;
		}
		str[strlen(str)-1] = '\0';
		// Transforma as letras maiusculas em minusculas
		minuscula(str);
		strcpy(dicio->palavras[dicio->linhas], str);
		dicio->linhas++;
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

	for(i = 0; i <= dicio->linhas; i++)
		free(dicio->palavras[i]);

	free(dicio->palavras);

	dicio->palavras = NULL;
	dicio = NULL;
}

// Função de comparação para o sort
int cmpfunc(const void * a, const void * b){
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	return strcmp(*ia, *ib);
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

/* Busca palavra no dicionário
	Retorna 1 caso esteja no dicionário e 0 caso contrário*/
int busca_dicio(tad_dicio *dicio, char *palavra){
	int *busca;

	busca = (int*) bsearch(&palavra, dicio->palavras, dicio->linhas, sizeof(char*), cmpfunc);
	if(busca != NULL)
		return 1;
	return 0;
}