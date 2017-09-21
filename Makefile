all:
	@cd src; make all
	@make run
	@cp Huffman ./bin/Huffman
run:
	@g++ -o Huffman ./src/main.o ./src/myHuffman.o ./src/tree.o ./src/util.o
clean:
	@rm -f Huffman
	@cd src/; make clean
