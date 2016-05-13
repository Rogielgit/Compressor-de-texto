all:
   	
	@gcc -std=c99 -c Compressor.c
	@gcc -std=c99 -c Huffman/HeapEstatica.c
	@gcc -std=c99 -c Huffman/Huffman.c
	@gcc -std=c99 -c Huffman/ArvoreBinaria.c
	@gcc -std=c99 -c Runlenght/runlenght.c
	@gcc -std=c99 -c BWT/bwt.c
 
	@gcc Compressor.o HeapEstatica.o Huffman.o ArvoreBinaria.o runlenght.o bwt.o -o Compressor

run:
	@./Compressor
