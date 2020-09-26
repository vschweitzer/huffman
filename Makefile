OUTPUT=huffman
EXTRA=-Wall -Wextra -pedantic -g3 -O0

all: compress.o util.o main.o
	gcc $(EXTRA) $^ -o $(OUTPUT)

main.o: main.c
	gcc $(EXTRA) -c $^

util.o: util.c
	gcc $(EXTRA) -c $^

compress.o: compress.c
	gcc $(EXTRA) -c $^

clean: 
	rm -f *.h.gch
	rm -f *.o
	rm -f $(OUTPUT)
