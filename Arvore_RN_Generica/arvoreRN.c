/*
	Autor: 
        Yuri Celeste Pulier	
	Nome:
		arvoreRN.c
    Referencias:
        https://ava.ufes.br/pluginfile.php/286636/mod_resource/content/1/aula10-Rubro-Negra.pdf
        https://www.ime.usp.br/~song/mac5710/slides/08rb.pdf
        http://docente.ifrn.edu.br/robinsonalves/disciplinas/estruturas-de-dados/ArvRN.pdf
*/

// Inclusão das bibliotecas no programa
#include "libRN.h"

//Função de alocação de um novo nó
void criaNoRN(void* informacao, No** no){
    No *novo = (No*)calloc(1, sizeof(No));
    novo->info = informacao;
    novo->cor = 'R';
    novo->dir = externo;
    novo->esq = externo;
    novo->pai = externo;
    (*no) = novo;
}

// Função de busca de uma dada info na árvore rubro-negra
No* buscaRN (void* ch, No *aux, No **pai, int(*comp)(void*, void*)){
    // ao tentar fazer aux->pai, não estava conseguindo encontrar esse ponteiro durante a inserção dos nós, pois sua atualização estava 
    //incorreta, portanto foi necessário utilizar No** pai, na passagem de parâmetros. O ponteiro aux->pai é atualizado na main.
    if(aux == externo){
        return externo;
    }
    else{
        if(comp(ch, aux->info) == 1){
            (*pai) = aux;
            aux = buscaRN(ch, aux->dir, pai, comp);
        }
        else if(comp(ch, aux->info) == -1){
            (*pai) = aux;
            aux = buscaRN(ch, aux->esq, pai, comp);
        }
        else if(comp(ch, aux->info) == 0) return aux;
    }
}

// Função para impressão da Arvore Rubro-negra
void imprimeRN (No *T, int nivel, void(*imp)(void*)){
    if(T != externo){
        imprimeRN(T->esq, nivel+1, imp);
        int i;
        for(i=0; i<nivel; i++) printf("\t");
        imp(T->info);  printf(":%c\n", T->cor);
        imprimeRN(T->dir, nivel+1, imp);
    }
}

// Função para buscar o sucessor de um nó na árvore
void sucessorRN (No **aux, No **sucessor, No **paisucessor){
    (*paisucessor) = (*aux);
    (*sucessor) = (*aux)->dir;  // caso (*aux)->dir seja um no externo, sucessor já será externo, se não, se for um nó interno:
    if((*sucessor) != externo) {
        while((*sucessor)->esq != externo){
            (*paisucessor) = (*sucessor);
            (*sucessor) = (*sucessor)->esq;
        }
    }
}

//Funcao de rotacao para a direita
void rotacaoDir(No** T, No** v){
    No *u = (*v)->esq;
    (*v)->esq = u->dir;
    u->dir = (*v);
    if((*v) == (*v)->pai->dir) (*v)->pai->dir = u;
    else (*v)->pai->esq = u;
    u->pai = (*v)->pai;
    (*v)->pai = u;
    //Se o pai de T não for mais um nó externo, então ele deixou de ser a raiz e a nova raiz será seu novo pai
    if((*T)->pai != externo) (*T) = (*T)->pai;
}

//Funcao de rotacao para a esquerda
void rotacaoEsq(No** T, No** v){
    No* u = (*v)->dir;
    (*v)->dir = u->esq;
    u->esq = (*v);
    if((*v) == (*v)->pai->dir) (*v)->pai->dir = u;
    else (*v)->pai->esq = u;
    u->pai = (*v)->pai;
    (*v)->pai = u;
    //Se o pai de T não for mais um nó externo, então ele deixou de ser a raiz e a nova raiz será seu novo pai
    if((*T)->pai != externo) (*T) = (*T)->pai;
}

//Função que conserta a árvore RN após a inserção
void insereFixUp(No** T, No** x){
    No *tio = externo;
    while((*x)->pai->cor == 'R'){
        //Se pai de x é filho a esquerda do avô de x
        if((*x)->pai == (*x)->pai->pai->esq){
            tio = (*x)->pai->pai->dir;
            //Se a cor do tio de x for Rubro
            if(tio->cor == 'R'){
                //Caso 1
                (*x)->pai->cor = 'N';
                tio->cor = 'N';
                (*x)->pai->pai->cor = 'R';
                (*x) = (*x)->pai->pai;
            }else{  //Se a cor do tio de x for Negro
                //Se x for filho a direita de pai
                if((*x) == (*x)->pai->dir){
                    //Caso 2
                    (*x) = (*x)->pai;
                    rotacaoEsq(T, x);
                }
                //Caso 3
                (*x)->pai->cor = 'N';
                (*x)->pai->pai->cor = 'R';
                (*x)=(*x)->pai->pai;
                rotacaoDir(T, x);
            }
        }
        else{
            tio = (*x)->pai->pai->esq;
            //Se a cor do tio de x for Rubro
            if(tio->cor == 'R'){
                //Caso 1
                (*x)->pai->cor = 'N';
                tio->cor = 'N';
                (*x)->pai->pai->cor = 'R';
                (*x) = (*x)->pai->pai;
            }else{  //Se a cor do tio de x for Negro
                //Se x for filho a esquerda de pai
                if((*x) == (*x)->pai->esq){
                    //Caso 2
                    (*x) = (*x)->pai;
                    rotacaoDir(T, x);
                }
                //Caso 3
                (*x)->pai->cor = 'N';
                (*x)->pai->pai->cor = 'R';
                (*x)=(*x)->pai->pai;
                rotacaoEsq(T, x);
            }
        }
    }
    (*T)->cor = 'N';
}

// Função para inserir um nó na árvore
void insereRN(void* ch, No *aux, No **T, int(*comp)(void*, void*)){
    // Quando a busca desce até os nós externos podemos inserir o novo nó
    No* no = NULL;
    criaNoRN(ch, &no);
    // Se a árvore for composta apenas pelo nó externo
    if((*T) == externo){
        no->cor = 'N';
        (*T) = no;
    }
    // Se a arvore tem nós internos 
    else{
        // inserção do novo nó na árvore 
        if(comp(ch, aux->pai->info) == 1) aux->pai->dir = no;
        else aux->pai->esq = no;
        no->pai = aux->pai;
        insereFixUp(T, &no);
    }
}

//Função que conserta a árvore RN após a inserção
// x é o nó que ficou no lugar do nó físicamente removido | corRemovido é a cor do nó que contém a info na qual foi pedido a remoção
void removeFixUp(No **x, No **irmao, No **pai, No **sucessor, No **T, char corRemovido){
    // QUANDO UM NÓ NEGRO É REMOVIDO, UMA DE SUAS SUBÁRVORES DESEQUILIBRA
    if(corRemovido == 'N'){
        //SÓ RESTOU UM ELEMENTO NA ÁRVORE, QUE ERA O SUCESSOR DO NÓ REMOVIDO E TAMBÉM É R                               
        if(((*sucessor)->cor == 'R') && ((*sucessor)->dir == externo && (*sucessor)->esq == externo) ){
            (*sucessor)->cor = 'N';
        }
        // EXISTEM MAIS ELEMENTOS NA ÁRVORE
        else{
            // CASO 1 = QUANDO O IRMÃO É RUBRO                                                              
            if((*irmao)->cor == 'R'){
                (*irmao)->cor = 'N';
                (*pai)->cor = 'R';
                //QUANDO X É FILHO À DIREITA DO PAI                                                
                if((*x) == (*pai)->dir){
                    rotacaoDir(T, pai);
                    (*x)->cor = 'N';
                }
                //QUANDO X É FILHO À ESQUERDA DO PAI                                               
                else{
                    rotacaoEsq(T, pai);
                    (*x)->cor = 'N';
                }
            }
            // CASO 2 = QUANDO IRMÃO E SEUS FILHOS SÃO NEGROS (no caso, os nós externos negros)
            else if( ((*irmao)->cor == 'N') && ((*irmao)->esq->cor == 'N') && ((*irmao)->dir->cor == 'N') ){
                (*irmao)->cor = 'R';
                No *irmaopai = externo, *avo = externo; 
                if((*pai) != (*T)) avo = (*pai)->pai;   
                if(avo != externo){
                    if((*pai) == avo->esq) irmaopai = avo->dir;
                    else irmaopai = avo->esq;
                    removeFixUp(pai, &irmaopai, &avo, sucessor, T, corRemovido);
                }
            }
            // CASO 3 = IRMÃO É FILHO A DIREITA DO PAI, QUANDO O IRMÃO E O FILHO DIREITO SÃO NEGROS E O FILHO ESQUERDO É RUBRO    
            else if(((*irmao) == (*pai)->dir) && ((*irmao)->cor == 'N') && ((*irmao)->dir->cor == 'N') && ((*irmao)->esq->cor == 'R')){
                // ROTAÇÃO DUPLA À ESQUERDA
                rotacaoDir(T, irmao);
                rotacaoEsq(T, pai);
                //ALTERAÇÃO DAS CORES
                (*pai)->cor = 'N';
                (*irmao)->cor = 'N';

            }
            //CASO 4 = IRMAO É FILHO A DIREITA DO PAI, IRMAO É NEGRO E SEU FILHO DIREITO É RUBRO                                  
            else if(((*irmao)->cor == 'N') && ((*irmao) == (*pai)->dir) && ((*irmao)->dir->cor == 'R')){
                // ALTERAÇÃO DE CORES
                (*irmao)->dir->cor = 'N';
                (*irmao)->cor = (*pai)->cor;
                (*pai)->cor = 'N';
                // ROTAÇÃO SIMPLES À ESQUERDA
                rotacaoEsq(T, pai);
            }
            // CASO 5 = IRMÃO É FILHO A ESQUERDA DO PAI, QUANDO IRMAO E O FILHO ESQUERDO SÃO NEGROS E O FILHO DIREITO É RUBRO     
            else if(((*irmao)->cor == 'N') && ((*irmao) == (*pai)->esq) && ((*irmao)->dir->cor == 'R') && ((*irmao)->esq->cor == 'N')){
                // ROTAÇÃO DUPLA À DIREITA
                rotacaoEsq(T, irmao);
                rotacaoDir(T, pai);
                //ALTERAÇÃO DAS CORES
                (*pai)->cor = 'N';
                (*irmao)->cor = 'N';
            }
            //CASO 6 = IRMAO É FILHO A ESQUERDA DO PAI, QUANDO IRMÃO É NEGRO E SEU FILHO ESQUERDO É RUBRO                         
            else if(((*irmao)->cor == 'N') && ((*irmao) == (*pai)->esq) && ((*irmao)->esq->cor == 'R')){
                //ALTERAÇÃO DAS CORES
                (*irmao)->esq->cor = 'N';
                (*irmao)->cor = (*pai)->cor;
                (*pai)->cor = 'N';
                //ROTAÇÃO SIMPLES À DIREITA
                rotacaoDir(T, pai);
            }
        }
    }
}

// Função para remover um nó da árvore
void removeRN(No **aux, No **T, int tamInfo){
    No *sucessor = externo, *paisucessor = externo;
    sucessorRN(aux, &sucessor, &paisucessor);
    if(sucessor == externo){
        if((*aux)->pai != externo){
            if((*aux)->pai->esq == (*aux)){
                (*aux)->pai->esq = (*aux)->esq;
                removeFixUp(&(*aux)->esq, &(*aux)->pai->dir, &(*aux)->pai, &sucessor, T, (*aux)->cor);
            }
            else if((*aux)->pai->dir == (*aux)){
                (*aux)->pai->dir = (*aux)->esq;
                removeFixUp(&(*aux)->dir, &(*aux)->pai->esq, &(*aux)->pai, &sucessor, T, (*aux)->cor);
            }
        }else (*T) = (*aux)->esq;
    }
    else{
        memcpy((*aux)->info, sucessor->info, tamInfo);
        if(paisucessor == (*aux)){
            paisucessor->dir = sucessor->dir;
            if(paisucessor->cor == 'R'){
                paisucessor->cor = sucessor->cor;
                paisucessor->esq->cor = 'R';
            }else{
                removeFixUp(&sucessor->dir, &(*aux)->esq, &(*aux), &sucessor, T, (*aux)->cor);
            }
        }
        else{
            paisucessor->esq = sucessor->dir;
            removeFixUp(&paisucessor->esq, &paisucessor->dir, &paisucessor, &sucessor, T, (*aux)->cor);
        }
    }
    (*T)->cor = 'N';
}
