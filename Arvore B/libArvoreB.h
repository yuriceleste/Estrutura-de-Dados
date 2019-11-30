/*
	Cabeçalho
*/


#ifndef _LIBARVOREB_H
#define _LIBARVOREB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ORDER 2

typedef struct pag {
	Artigo key[ORDER];		//vetor de chaves
	int n;					//quantidade de filhos na pagina (para realizar as verificaçoes)
	bool folha;				//indicador se a pagina eh uma folha ou nao
	struct pag *ptr[ORDER];	//vetor de ponteiro para as paginas
} Pag;

void createPag(Artigo* art);

void buscaB();




#endif