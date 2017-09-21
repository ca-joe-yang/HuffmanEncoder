all: main.o myHuffman.o tree.o util.o
	@cd ..
main.o: main.cpp myHuffman.o tree.o util.o
	@g++ -c main.cpp
myHuffman.o: myHuffman.cpp myHuffman.h tree.o util.o
	@g++ -c myHuffman.cpp
tree.o: tree.cpp tree.h util.o
	@g++ -c tree.cpp
util.o: util.h util.cpp
	@g++ -c util.cpp

clean:
	@rm -f *.o
