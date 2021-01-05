/*
	Autor: 
        Yuri Celeste Pulier	
	Nome:
		main.c
    Observações:
        Um exemplo de utilização da biblioteca libRN.h implementada com o objetivo da produção de uma estrutura de dados de Árvore Rubro Negra genérica.
    Referencias:
        https://ava.ufes.br/pluginfile.php/286636/mod_resource/content/1/aula10-Rubro-Negra.pdf
        https://www.ime.usp.br/~song/mac5710/slides/08rb.pdf
        http://docente.ifrn.edu.br/robinsonalves/disciplinas/estruturas-de-dados/ArvRN.pdf
*/

// Inclusão das bibliotecas no programa
#include "libRN.h"
// Constantes
#define TAM 10

typedef struct aluno{
    float matricula;
} Aluno;

void criaAluno(float mat, Aluno** a){
    Aluno *novo = (Aluno*)calloc(1, sizeof(Aluno));
    novo->matricula = mat;
    (*a) = novo;
}

// funcao que compara duas strings
/*int comparastr(void *s1, void *s2) {
    char *mat = *(char**)s1;
    Aluno *a = (Aluno*)s2;
    if(strcmp(mat, a->matricula) > 0) return 1;
    if(strcmp(mat, a->matricula) < 0) return -1;
    else return 0;
}

// funcao que compara dois inteiros
int comparaint(void *s1, void *s2) {
    int* mat = (int*)s1;
    Aluno* a = (Aluno*)s2;
    if ((*mat) > a->matricula)
        return 1;
    else if ((*mat) < a->matricula)
        return -1;
    else
        return 0;
}
*/
// funcao que compara dois floats
int comparafloat(void *s1, void *s2) {
    float* mat = (float*)s1;
    Aluno* a = (Aluno*)s2;
    if ((*mat) > a->matricula)
        return 1;
    else if ((*mat) < a->matricula)
        return -1;
    else
        return 0;
}

// funcao que imprime a matricula do aluno
void imprimeMat(void* a){
    Aluno* temp = (Aluno*)a;
    printf("%.2f", temp->matricula);
}

int main(){
    // Alocação do nó externo
    externo = (No*)calloc(1, sizeof(No));
    externo->cor = 'N';

    // Declaração das variáveis
    // T é a raiz da árvore
    No *T = externo, *aux = NULL, *pai = NULL;
    Aluno *newAluno = NULL;
    int op;
    
    /* Para escolher o tipo, basta tirar o comentario do tipo desejado, modificar a struct Aluno (ou criar outra struct que desejar),
        modificar a funcao criaAluno e informar qual função de comparação será utilizado nas funções de buscaRN() e insereRN().
        É necessário também a alteração do tipo de dado que será impresso na função imprimeMat() e especificar o tipo de dado
        que será lido pelo scanf()
    */
    //int mat;
    float mat;
    //char* mat = (char*)calloc(TAM, sizeof(char));

    do{
        printf("\n\n======================= MENU DE OPCOES =======================\n\t1 - INSERIR\n\t2 - REMOVER\n\t3 - IMPRIMIR\n\t0 - SAIR\n\n\t  Opcao: ");
        scanf("%d", &op);
        pai = externo;
        if(op == 1){
            fflush(stdin);
            printf("\n\tMATRICULA: ");
            scanf("%f", &mat);
            aux = buscaRN(&mat, T, &pai, &comparafloat);
            aux->pai = pai;
            if(aux != externo) printf("\n\tINSERCAO INVALIDA\n");   //Se for diferente de nó externo, um nó com essa chave já existe
            else{
                criaAluno(mat, &newAluno);
                insereRN(newAluno, aux, &T, &comparafloat);
            }
        }
        else if(op == 2){
            printf("\n\tELEMENTO:  ");
            scanf("%f", &mat);
            aux = buscaRN(&mat, T, &pai, &comparafloat);
            aux->pai = pai;
            if(aux == externo) printf("\n\tREMOCAO INVALIDA\n");
            else removeRN(&aux, &T, sizeof(Aluno));
        }
        else if(op == 3){
            printf("\n\n");
            if(T == externo) printf("\n  Arvore vazia.\n");
            else imprimeRN(T, 1, &imprimeMat);
        }
        else if(op >= 4 || op < 0){
            printf("\n\t OPCAO INVALIDA.\n");
        }
    }while(op != 0);

    printf("\n\tFIM DO PROGRAMA...\n\n");
}
