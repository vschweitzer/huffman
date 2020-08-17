EXTRA=-Wall -Wextra

all: 
	gcc $(EXTRA) tree.h error.h codeWord.h compress.h compress.c util.h util.c main.c -o huffman

util.o: util.h util.c
	gcc $(EXTRA) util.h util.c -o util.o



