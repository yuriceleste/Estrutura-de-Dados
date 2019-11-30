// Inclusão das bibliotecas no programa
#include "libQsExt.h"

void createPag(Artigo* art){
	Pag *newPag = (Pag*)calloc(1, sizeof(Pag));
	if(newPag == NULL)
		printf("\nErro ao criar nova pagina.\n");
	else
		//Nao sei ainda se esse for vai rodar, mas só coloquei pra saber que tem que 'zerar' os valores dos artigos dentro da pagina
		for(int i=1; i<ORDER; i++)
			key[i] = NULL;
		newPag->folha = true;
		newPag->n = 0;
}