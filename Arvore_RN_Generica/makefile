### Makefile ###

# Alvo all -> onde realizar 
all: exec

exec: arvoreRN.o main.o
	gcc -o exec arvoreRN.o main.o

main.o: main.c libRN.h
	gcc -c main.c

arvoreRN.o:	arvoreRN.c libRN.h
	gcc -c arvoreRN.c

# Alvo clean -> Apagar objetos (*.o) e outros arquivos temporarios 
clean:
	rm -rf *.o

### Referencia: http://www.inf.ufes.br/~pdcosta/ensino/2019-2-estruturas-de-dados/material/GuiaRapido_EDI.pdf ###