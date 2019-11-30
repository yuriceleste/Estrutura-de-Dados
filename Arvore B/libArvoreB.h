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
	Artigo key[(2*ORDER)+1];//vetor de chaves com max de 2d chaves, iniciando da posicao 1 do vetor
	int n;					//quantidade de filhos na pagina (para realizar as verificaçoes)
	bool folha;				//indicador se a pagina eh uma folha ou nao
	struct pag *ptr[(2*ORDER)+2];	//vetor de ponteiro para as paginas
} Pag;

void createPag(Artigo* art);

void buscaB(Pag* pt, int x, int f, int g);



#endif