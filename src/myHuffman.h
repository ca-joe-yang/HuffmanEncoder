#include <cstring>
#include "tree.h"

using namespace std;

class Compressor
{
public:
   Compressor() : _nodeTree() { _codeTable = new CodeTable; }
   ~Compressor() {}

   void reset() {}
   void clear() {}

   bool compressFile(const string& inputFile, const string& outputFile);
private:
   NodeTree   _nodeTree;
   CodeTable* _codeTable;
   
   void encoding(const string& inputFile, const string& outputFile);
   void printCompressionInfo(const string& inputFile, const string& outputFile);
};


class Decompressor
{
public:
   Decompressor() : _nodeTree() { _codeTable = new CodeTable; _root = 0; }
   ~Decompressor() {}
  
   bool decompressFile(const string& inputFile);
private:
   NodeTree   _nodeTree;
   CodeTable* _codeTable;
   Node*      _root;

   bool readCodeTable(ifstream&);
   void decoding(ifstream&);
};

