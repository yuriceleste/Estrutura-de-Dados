// Inclusão das bibliotecas no programa
#include "libQsExt.h"

void createPag(Artigo* art){
	Pag *newPag = (Pag*)calloc(1, sizeof(Pag));
	if(newPag == NULL)
		printf("\nErro ao criar nova pagina.\n");
	else
		newPag->folha = true;
		newPag->n = 0;
}

Pag* buscaB(Pag* pt, int x, int f, int g){
	Pag* p;
	int n, i;
	p = pt;
	f = 0;
	while(p != NULL){
		i = g = 1;
		pt = p;
		n = p->n;
		while(i<=n){
			if(x > p->key[i]){
				g = i+1;
				i = g;
			}else{
				if(x == p->key[i]){
					p = NULL;
					f = 1;
				}
				else{
					p = p->ptr[i-1];
				}
				i = n+2;
			}
		}
		if(i == n)
			p = p->ptr[n];
	}
}