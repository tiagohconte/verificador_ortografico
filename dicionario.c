/*	Feito por Tiago Henrique Conte	
	Trabalho da disciplina de Programa��o 2 do BCC UFPR
	Verificador Ortogr�fico	
	Implementa��o de fun��es da biblioteca dicion�rio	*/

#include "dicionario.h"
// Define o quanto de mem�ria ser� alocado por opera��o de aloc
#define VALOR_ALOC 50000

/* Fun��o para carregar o dicion�rio na mem�ria */
int carrega_dicionario(tad_dicio *dicio){
	// Abre arquivo do dicion�rio
	FILE *arq_dicio;
	int num_aloc = 1;		// Registra o n�mero de aloca��es feitas	

	dicio->linhas = 0;
	dicio->palavras = NULL;
	
	// Aloca��o de espa�o inicial na mem�ria
	dicio->palavras = realloc(dicio->palavras, (num_aloc * VALOR_ALOC) * sizeof(dicio->palavras));
	if(dicio->palavras == NULL){
		fprintf(stderr, "Erro na aloca��o inicial do dicion�rio.\n");
		return 0;
	}

	// L� o arquivo dicion�rio e guarda na mem�ria
	arq_dicio = fopen(DIR, "r");
	if(!arq_dicio){
		fprintf(stderr, "Erro ao abrir arquivo dicion�rio.");
		return 0;
	}

	char str[SIZE+1];
	while(!feof(arq_dicio)){
		// Verifica se a aloca��o feita anteriormente aidna � suficiente para o n�mero de linhas
		if(dicio->linhas == (num_aloc * VALOR_ALOC)){
			num_aloc++;
			dicio->palavras = realloc(dicio->palavras, (num_aloc * VALOR_ALOC) * sizeof(dicio->palavras));
		}

		fgets(str, SIZE, arq_dicio);
		// Aloca espa�o para a palavra		
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
		Portanto � feita a reoordena��o das palavras */
	qsort(dicio->palavras, dicio->linhas, sizeof(char*), cmpfunc);

	fclose(arq_dicio);	
	return 1;
}

// Libera espa�o da mem�ria
void descarrega_dicionario(tad_dicio *dicio){
	int i;

	for(i = 0; i <= dicio->linhas; i++)
		free(dicio->palavras[i]);

	free(dicio->palavras);

	dicio->palavras = NULL;
	dicio = NULL;
}

// Fun��o de compara��o para o sort
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

/* Busca palavra no dicion�rio
	Retorna 1 caso esteja no dicion�rio e 0 caso contr�rio*/
int busca_dicio(tad_dicio *dicio, char *palavra){
	int *busca;

	busca = (int*) bsearch(&palavra, dicio->palavras, dicio->linhas, sizeof(char*), cmpfunc);
	if(busca != NULL)
		return 1;
	return 0;
}