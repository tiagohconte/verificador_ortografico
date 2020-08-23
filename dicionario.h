/*	Feito por Tiago Henrique Conte	
	Trabalho da disciplina de Programa��o 2 do BCC UFPR
	Verificador Ortogr�fico	
	Biblioteca Dicion�rio	*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DIR "brazilian"
#define SIZE 50

/*Defini��o do tipo dicionario*/
typedef struct tad_dicio {
	int linhas;
	char **palavras;
} tad_dicio;

/* Fun��o para carregar o dicion�rio na mem�ria */
int carrega_dicionario(tad_dicio *dicio);

// Libera espa�o da mem�ria
void descarrega_dicionario(tad_dicio *dicio);

// Fun��o de compara��o para o sort
int cmpfunc(const void * a, const void * b);

// Transforma uma string em totalmente minuscula
void minuscula(char *str);

//Busca palavra no dicion�rio
int busca_dicio(tad_dicio *dicio, char *palavra);