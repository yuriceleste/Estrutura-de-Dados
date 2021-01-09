# Estrutura de Dados



## Árvore Rubro Negra - Genérica

Árvore rubro-negra é um tipo de árvore binária de busca balanceada que possui um bit de dados separado para armazenar a cor de cada nó, que pode ser RUBRO ou NEGRO.
Cada nó é composto peloes seguintes campos:
- valor (dados armazenados no nó)
- filho esquerdo
- filho direito
- pai

Dentre as melhorias dessa estrutura de dados podemos observar um melhor tempo de execução para suas operações, como a busca, inserção e remoção dos nós com um tempo de O(log n). Para que esse balanceamento seja possível, a árvore rubro-negra possui algumas propriedades que devem ser satisfeitas:
1. Todo nó é rubro ou negro.
2. A raiz sempre deve ser negra.
3. Toda a folha (nil) deve ser preta.
4. Se um nó é rubro, seus filhos devem ser negros.
5. Para cada nó da árvore, os caminhos até as folhas devem conter o mesmo número de nós negros.

Se todas as propriedades forem cumpridas, a árvore estará balanceada, caso contrário, devem ser utilizados métodos como rotação e mudança de cores nos nós da árvore para torna-la novamente balanceada.

Exemplo de Árvore rubro-negra balanceada:

![arvore1](https://github.com/yuripulier/Estrutura_de_Dados/blob/master/images/arvore-rn-balanceada.png "Arvore RN balanceada")


Uma estrutura de dados genérica é aquela que aceita qualquer tipo de dados para serem armazenados, que trabalham de forma transparente para o usuário final (programador), independentemente do tipo de dado que está sendo manipulado, sejam elas int, float, char, struct e entre outros. Podemos definir alguns pontos importantes sobre as características desse tipo abstrato de dados (TAD) genérico:
- Uma estrutura genérica deve ser capaz de armazenar qualquer tipo de informação.
- O TAD deve desconhecer o tipo da informação.
- As funções TAD não podem manipular diretamente as informações.
- O cliente do TAD genérico tem a responsabilidade das operações de acesso à informação.

Exemplo TAD Genérico:

![TAD-Generico](https://github.com/yuripulier/Estrutura_de_Dados/blob/master/images/TAD-Generico.png "TAD Genérico")



## Quicksort Externo

O Quicksort externo é um algoritmo que utiliza o paradigma de divisão e conquista, e ordana in situ um arquivo de n registros. Os registros encontram-se armazenados consecutivamente em memória secundária de acesso randômico e o algoritmo possui uma complexidade de O(log n) unidades de memória interna.


Para ordenar um arquivo A = {R1, ..., Rn}, o algoritmo particiona A como segue:

{R1, ..., Ri} ≤ Ri+1 ≤ Ri+2 ≤ ... ≤ Rj−2 ≤ Rj−1 ≤ {Rj, ... , Rn};

e chama recursivamente o algoritmo em cada um dos subarquivos gerados.


Autor: Yuri Celeste Pulier

Data: 2019
