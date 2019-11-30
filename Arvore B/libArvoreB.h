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

/*Nome: createPag
        Variáveis: *art uma struct do tipo Artigo que sera armazenada num no da pagina, 
        Objetivos: criar uma nova pagina na Arvore B*/
void createPag(Artigo* art);

/*Nome: buscaB
        Variáveis: *pt que aponta para a pagina onde a chave foi encontrada, x é a chave a ser procurada, f informa se a chave foi 
        	ou nao encontrada e g informa a posicao na pagina onde foi encontrada a chave x
        Objetivos: buscar a chave x informada na Arvore B*/
void buscaB(Pag* raiz, Pag** pt, int x, int* f, int* g);



#endif