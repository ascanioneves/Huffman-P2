COMPRESS = Huff/Compress.c
DESCOMPRESS = Huff/Descompress.c
BINARY_TREE = Estruturas/HuffmanTree.c
HASH = Estruturas/HuffmanHash.c
HEAP = Estruturas/HuffmanHeap.c
MAIN = Huff/Main.c
TEST_C = Testes/Test.c

compile_huffman:
	gcc $(COMPRESS) $(DESCOMPRESS) $(HUFFMAN) $(BINARY_TREE) $(HASH) $(HEAP) $(MAIN) -o huffman

compile_test:
	gcc $(HUFFMAN) $(BINARY_TREE) $(HASH) $(HEAP) $(TEST_C) -o test_cunit -w -lcunit