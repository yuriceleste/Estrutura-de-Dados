// Inclusão das bibliotecas no programa
#include "libQsExt.h"

typedef struct artigo{
    int id;
    //int ano;
    //char autor[200];
    //char titulo[200];
    //char revista[200];
    //char DOI[20];
    //char palavraChave[200];
} Artigo;

void criaArtigo(int id, Artigo** art){
    Artigo *novo = (Artigo*)calloc(1, sizeof(Artigo));
    novo->id = id;
    (*art) = novo;
}

int main(){
	int op, id, f=0, g=0;

	FILE *Arq;
	Pag* raiz = NULL;

	Artigo* newArtigo = NULL;

	do{
		printf("\n\n======================= MENU DE OPCOES =======================\n");
		printf("\t1 - INSERIR\t2 - REMOVER\n\t3 - IMPRIMIR\t0 - SAIR\n\n\t  Opcao: ");
        scanf("%d", &op);

        if(op == 1){
            printf("\n\t ID: ");
            scanf("%d",&id);
            buscaB(&raiz, id, &f, &g);
            if(f == 1)
            	printf("\n\tInsercao invalida! Id informado ja se encontra na tabela.\n");
            else if(f = 0){
            	criaArtigo(id, &newArtigo);
            	insereB(newArtigo, g);
            	printf("\n\tInsercao realizada com sucesso!\n");
            }
        }
        else if(op == 2){
            
        }
        else if(op == 3){

        }
        else if((op < 0) || (op > 3))
        	printf("\n\tOpcao invalida!");
	}while(op != 0);
		

	printf("\n\tFIM DO PROGRAMA...\n\n");

    return 0;
}