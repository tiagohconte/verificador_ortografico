/*	GRR20190374 Tiago Henrique Conte
	Feito por Tiago Henrique Conte	
	Trabalho da disciplina de Programação 2 do BCC UFPR
	Verificador Ortográfico	
	Biblioteca Dicionário	*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __DIC__
#define __DIC__

#define DIR "brazilian"
#define SIZE 50		// Define o número máximo de letras em uma palavra
#define VALOR_ALOC 50000	// Define o quanto de memória será alocado por operação de aloc

/*Definição do tipo dicionario*/
typedef struct tad_dicio {
	int linhas;
	char **palavras;
} tad_dicio;

/* Função para carregar o dicionário na memória */
int carrega_dicionario(tad_dicio *dicio);

// Libera espaço da memória
void descarrega_dicionario(tad_dicio *dicio);

// Transforma uma string em totalmente minuscula
void minuscula(char *str);

//Busca palavra no dicionário
int busca_dicio(tad_dicio *dicio, char *palavra);

#endif