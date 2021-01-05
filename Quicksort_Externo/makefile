### Makefile ###

# Alvo all -> onde realizar 
all: exec

exec: QuickSortExterno.o main.o
	gcc -o exec QuickSortExterno.o main.o

main.o: main.c libQsExt.h
	gcc -c main.c

QuickSortExterno.o:	QuickSortExterno.c libQsExt.h
	gcc -c QuickSortExterno.c

# Alvo clean -> Apagar objetos (*.o) e outros arquivos temporarios 
clean:
	rm -rf *.o

### Referencia: http://www.inf.ufes.br/~pdcosta/ensino/2019-2-estruturas-de-dados/material/GuiaRapido_EDI.pdf ###