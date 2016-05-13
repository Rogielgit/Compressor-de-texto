all:
   	
	@gcc -std=c99 -c main.c
	@gcc -std=c99 -c HeapEstatica.c
	@gcc -std=c99 -c Huffman.c
	@gcc -std=c99 -c ArvoreBinaria.c
	
	@gcc main.o HeapEstatica.o Huffman.o ArvoreBinaria.o -o Compressor

run:
	@./Compressor
