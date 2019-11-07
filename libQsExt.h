/*
    Autor: Yuri Celeste Pulier
    
    Objetivo: Criar um pacote de Quicksort Externo para tipo Genérico de dados.

    Observações: includes <limits.h> e <float.h> são utilizados para definir o limite superior e inferior dos tipos de dados a serem inseridos
    ou o usuário do pacote pode inserir manualmente os parâmetros. Os limites para char foram utilizados de acordo com a tabela ASCII.
*/

#ifndef _LIBQSEXT_H
#define _LIBQSEXT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

#define TAM_AREA 3


/*Nome: struct registro
        Variáveis: registro de um dado genérico a ser inserido no arquivo
        Objetivos: conter alguma informação para que seja trabalhado dentro do arquivo
        Apelido: Registro*/
typedef struct registro{
	void* chave;
}Registro;

/*Nome: criaReg:
        Objetivo: recebe um valor como paraetro e cria um registro
*/
void criaReg(void* ch, Registro* R);

/*Nome: inserirArea 
        Parametros: Area na memória interna, ultimo registro lido e a quantidade de registros na Area
        Objetivos: criar um novo nó
        */
void inserirArea(Registro *Area, Registro *UltLido, int *NRArea, int(*comp)(void*, void*));

/*Nome: QuickSortExterno
        Objetivo: Ordenar um arquivo com registros
        Parâmetros: O arquivo incialmente desordenado com regitros, 
                    arquivo auxiliar no particionamento,
                    arquivo auxiliar no particionamento,
                    posição inicial e final do arquivo desordenado
                    funcao de comparacao utlizada
*/
void QuickSortExterno (FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, char* nomeArq, int Esq, int Dir, void* LimInf, void* LimSup, int(*comp)(void*, void*));

/*Nome: LeSup
        Objetivo: realiza a leitura do registro superior presente no e invai
                arquivo e decrementa o contador (Ls)
*/
void LeSup(FILE **ArqLEs, char* nomeArq, Registro **UltLido, int *Ls, bool *OndeLer);

/*Nome: LeInf
        Objetivo: realiza a leitura do registro inferior presente no 
                arquivo e incremnta o contador (Li)
*/
void LeInf(FILE **ArqLi, char* nomeArq, Registro **UltLido, int *Li, bool *OndeLer);

/*Nome: EscreveMax
        Objetivo: Realiza a escrita superior do registro no arquivo 
        e decrementa o contador (Es)
*/
void EscreveMax(FILE **ArqLEs, char* nomeArq, Registro *R, int *Es);

/*Nome: EscreveMin
        Objetivo: Realiza a escrita inferior do registro no arquivo 
        e incrementa o contador (Ei)
*/
void EscreveMin (FILE **ArqEi, char* nomeArq, Registro *R, int *Ei);

/*Nome: RetiraMax
        Objetivo: Remover o maioir registro presente no
        vetor Area na memória principal
*/
void RetiraMax(Registro *Area, Registro *R, int *NRArea);

/*Nome: RetiraMin
        Objetivo: Remover o menor registro presente no
        vetor Area na memória principal
*/
void RetiraMin(Registro *Area, Registro *R, int *NRArea);

/*Nome: Particiona
        Objetivo: Realiza o particionamento do arquivo desordenado
        Parâmetros: O arquivo incialmente desordenado com regitros, 
                    arquivo auxiliar no particionamento,
                    arquivo auxiliar no particionamento,
                    vetor de registros ordenados em memória principal,
                    posição inicial do arquivo desordenado
                    posição em que o registro é menor que o limite inferior
*/
void Particiona(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, char* nomeArq, Registro *Area, int Esq, int Dir, int *i, int *j, void* LimInf, void* LimSup, int(*comp)(void*, void*));

/*Nome: imprimeArq
        Objetivo: imprimir na tela os registros presentes no arquivo
*/
void imprimeArq(FILE *ArqLi, char* nomeArq, void(*imp)(void*));


#endif