// Inclusão das bibliotecas no programa
#include "libQsExt.h"

// Um exemplo de utilização do pacote QuickSortExterno.c, utilizando a biblioteca libQsExt.h

typedef struct cliente{
    int identidade;
    char nome[60];
} Cliente;

void criaCliente(int id, char* nome, Cliente** c){
    Cliente *novo = (Cliente*)calloc(1, sizeof(Cliente));
    novo->identidade = id;
    strcpy(novo->nome, nome);
    (*c) = novo;
}

// funcao que compara duas strings
int comparastr(void *s1, void *s2) {
    Cliente *c1 = (Cliente*)s1;
    Cliente *c2 = (Cliente*)s2;
    if(strcmp(c1->nome, c2->nome) > 0) return 1;
    if(strcmp(c1->nome, c2->nome) < 0) return -1;
    else return 0;
}

// funcao que compara dois inteiros
int comparaint(void *s1, void *s2) {
    Cliente* c1 = (Cliente*)s1;
    Cliente* c2 = (Cliente*)s2;
    if (c1->identidade > c2->identidade)
        return 1;
    else if (c1->identidade < c2->identidade)
        return -1;
    else
        return 0;
}   
/*
// funcao que compara dois floats
int comparafloat(void *s1, void *s2) {
    Cliente* c1 = (Cliente*)s1;
    Cliente* c2 = (Cliente*)s2;
    if (c1->identidade > c2->identidade)
        return 1;
    else if (c1->identidade < c2->identidade)
        return -1;
    else
        return 0;
}
*/
// funcao que imprime a matricula do aluno
void imprimeCliente(void* c){
    Cliente* temp = (Cliente*)c;
    printf("%d", temp->identidade);
    printf(" - %s", temp->nome);
}

int main(){
	int op, tam, criterio;

	FILE *ArqLEs; //Gerencia o LS e o Es
	FILE *ArqLi;  //Gerencia o Li
	FILE *ArqEi;  //Gerencia Ei

	Cliente* newClient = (Cliente*)calloc(1, sizeof(Cliente));
    
	Cliente *LimInf, *LimSup;
    // Pela tabela ASCII, o "@" está antes dos caracteres usados para nome e o "{", depois.
    criaCliente(INT_MIN, "@", &LimInf);
    criaCliente(INT_MAX, "{", &LimSup);

    Registro R;

    int id;           // INT_MIN, INT_MAX
    char nome[60];    // CHAR_MIN, CHAR_MAX
    
	do{
        printf("\n\n======================= MENU DE OPCOES =======================\n\t1 - INSERIR\n\t2 - ORDENAR\n\t3 - IMPRIMIR\n\t0 - SAIR\n\n\t  Opcao: ");
        scanf("%d", &op);
        if(op == 1){
            fflush(stdin);
            printf("\n Quantidade de Registros: ");
            scanf("%d", &tam);
            //Abrindo o arquivo para escrever os registros
            ArqLi = fopen("teste.dat", "wb");
            if(ArqLi == NULL){
                printf("Arquivo não pode ser escrito.");
            }else{
                //Inserindo os registros no arquivo
                for(int i = 0; i<tam; i++){
                    printf("\n\tID do Cliente %d: ", i+1);
                    scanf("%d", &id);
                    printf("\n\tNome do Cliente %d: ", i+1);
                    scanf("%s", nome);
                    criaCliente(id, nome, &newClient);
                    criaReg(newClient, &R);
                    fwrite(&R, sizeof(Registro), 1, ArqLi);
                }
            }
            fclose(ArqLi);
        }
        else if(op == 2){
            printf("\n========== Criterio de Ordenacao ========== ");
            printf("\n\t 1. ID\t\t 2. Nome\n\n\t   Criterio: ");
            scanf("%d", &criterio);
            if(criterio == 1){
                QuickSortExterno(&ArqLi, &ArqEi, &ArqLEs, "teste.dat", 0, (tam-1), LimInf, LimSup, &comparaint);
                printf("\n\tOrdenação realizada com sucesso!\n");
            }
            if(criterio == 2){
                QuickSortExterno(&ArqLi, &ArqEi, &ArqLEs, "teste.dat", 0, (tam-1), LimInf, LimSup, &comparastr);
                printf("\n\tOrdenação realizada com sucesso!\n");
            }
            else if(criterio != 1 && criterio != 2){
                printf("\n\tCriterio invalido.\n");
            }
        }
        else if(op == 3){
            //Abre o arquivo para leitura
            imprimeArq(ArqLi, "teste.dat", &imprimeCliente);
        }
    }while(op != 0);

    printf("\n\tFIM DO PROGRAMA...\n\n");

    return 0;
}