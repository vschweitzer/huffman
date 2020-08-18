OUTPUT=huffman
EXTRA=-Wall -Wextra -pedantic

all: compress.o util.o main.o
	gcc $(EXTRA) $^ -o $(OUTPUT)

main.o: main.c
	gcc -c $^

util.o: util.c
	gcc $(EXTRA) -c $^

compress.o: compress.c
	gcc $(EXTRA) -c $^

clean: 
	rm -f *.h.gch
	rm -f *.o
	rm $(OUTPUT)
