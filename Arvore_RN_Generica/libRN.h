/*
	Autor: Yuri Celeste Pulier	
	Nome:
		libRN.h

	Observacoes: 
		Criacao de arvore binaria de busca, remocao, insercao, busca e altura de um no, utilizando o tipo inteiro
        A variável void* ch é o valor da matrícula no exemplo utilizado da struct Aluno

    Referencias:
        https://ava.ufes.br/pluginfile.php/286636/mod_resource/content/1/aula10-Rubro-Negra.pdf
        https://www.ime.usp.br/~song/mac5710/slides/08rb.pdf
        http://docente.ifrn.edu.br/robinsonalves/disciplinas/estruturas-de-dados/ArvRN.pdf
*/	

#ifndef _LIBRN_H
#define _LIBRN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Nome: struct no
        Variáveis: informação de um dado genérico a ser inserido no nó, a cor do nó, ponteiro para o pai, filho direito e filho esquerdo
        Objetivos: Estrutura de um nó utilizado para a criação de uma árvore RN
        Apelido: No */
typedef struct no{
    void* info;
    char cor;
    struct no *dir,*esq, *pai;
} No;

// Nó externo que indicará o fim da árvore
No *externo;

/*Nome: criaNo 
        Parametros: um tipo de dado genérico e um endereço para o novo nó a ser criado
        Objetivos: criar um novo nó*/
void criaNoRN(void* info, No **no);

/*Nome: buscaRN 
        Parametros: uma ch de um tipo genérico de dado, a raiz da árvore, um endereço para o pai e a função de comparação à ser utilizada
        Objetivos: buscar um nó que contenha o valor de ch na árvore, além de modificar o valor do pai do nó a ser procurado
        Retorno: o nó encontrado ou um nó externo, caso não haja um nó com esse ch na árvore RN*/
No* buscaRN (void* ch, No *aux, No **pai, int(*comp)(void*, void*));

/*Nome: imprimeRN
        Parametros: a raiz da árvore, o primeiro nível e a função de impressão à ser utilizada de um tipo de dado específico
        Objetivos: imprimir a informação contida nos nós da árvore RN*/
void imprimeRN (No *T, int nivel, void(*imp)(void*));

/*Nome: insereFixUp 
        Parametros: o endereço da raiz da árvore e o endereço do novo nó inserido na árvore RN 
        Objetivos: alterar as configurações da árvore após a inserção de um novo nó, para obedecer as propriedade de árvore RN*/
void insereFixUp (No **T, No **x);

/*Nome: insereRN 
        Parametros: um dado genérico a ser inserido na árvore RN, o resultado da busca, a raiz da árvore e uma função de comparação
        Objetivos: inserir um novo nó na árvore RN*/
void insereRN (void* info, No *aux, No **T, int(*comp)(void*, void*));

/*Nome: sucessorRN
        Parametros: o endereço de um nó da árvore, o endereço do sucessor desse nó, e um endereço para o pai do sucessor desse nó
        Objetivos: encontrar o sucessor e o pai do sucessor do nó especificado nos parâmetros*/
void sucessorRN (No **no, No **sucessor, No **paisucessor);

/*Nome: removeFixUp
        Parametros: endereço para nó que ocupou a posição do nó removido fisicamente na árvore, o endereço para o irmao desse nó, o
            endereço para o pai desse nó, o endereço para o sucessor desse nó, a raiz da árvore e a cor do nó removido
        Objetivos: alterar as configurações da árvore após a remoção de um novo nó, para obedecer as propriedades de árvore RN*/
void removeFixUp (No **x, No **irmao, No **pai, No **sucessor, No **T, char corRemovido);

/*Nome: removeRN
        Parametros: endereço para o nó resultante da busca, a raiz da árvore e o tamanho do tipo de dados genérico específico
        Objetivos: remover o no aux da árvore RN*/
void removeRN (No **aux, No **T, int tamInfo);

/*Nome: rotacaoEsq
        Parametros: endereço para a raiz da árvore e o nó no qual será realizado a rotação
        Objetivos: rotacionar para a esquerda a partir do nó informado*/
void rotacaoEsq (No** T, No **v);

/*Nome: rotacaoDir
        Parametros: endereço para a raiz da árvore e o nó no qual será realizado a rotação
        Objetivos: rotacionar para a direita a partir do nó informado*/
void rotacaoDir (No **T, No **v);


#endif
