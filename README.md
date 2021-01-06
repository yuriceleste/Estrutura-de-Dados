# Estrutura de Dados



### Arvore Rubro Negra - Genérica

Arvore rubro-negra é um tipo de árvore binária de busca balanceada e possuem um bit de dados separado para armazenar a cor de cada nó, que pode ser RUBRO ou NEGRO.
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

Caso todos as propriedades sejam cumpridas, a árvore estará balanceada, caso contrário, devem ser utilizados métodos como rotação e mudança de cores nos nós da árvore para tornar a árvore novamente balanceada.
Alguns exemplo de Árvore rubro-negra balanceada:
!http://prntscr.com/whsp1h


### Quicksort Externo



Autor: Yuri Celeste Pulier

Data: 2019
