### Makefile ###

# Alvo all -> onde realizar 
all: exec

exec: arvoreB.o main.o
	gcc -o exec arvoreB.o main.o

main.o: main.c libArvoreB.h
	gcc -c main.c

arvoreB.o:	arvoreB.c libArvoreB.h
	gcc -c arvoreB.c

# Alvo clean -> Apagar objetos (*.o) e outros arquivos temporarios 
clean:
	rm -rf *.o