#include <fstream>
#include <cstring>
#include "myHuffman.h"
#include "util.h"

using namespace std;

bool Compressor::compressFile(const string& inputFile, const string& outputFile) 
{
   cout << "Compressing File  \"" << inputFile << "\" ..." << endl;
   ifstream input;
   input.open(inputFile.c_str());
   if (input == 0) return false;
   _nodeTree.init(input);
   input.close();
   _nodeTree.genTreeFromLeaf(_nodeTree.size());
   //_nodeTree.print();
   _nodeTree.genCodeTable(_codeTable);
   encoding(inputFile, outputFile);
   printCompressionInfo(inputFile, outputFile);
   return true;
}

void Compressor::encoding(const string& inputFile, const string& outputFile) 
{
   ofstream output;
   output.open(outputFile.c_str());
   output << "huff " << _nodeTree.getCharNodeNum() << endl;
   for (size_t i = 0; i < _codeTable->size(); ++i) {
      if ((*_codeTable)[i] != "")
         output << i << " " << (*_codeTable)[i] << endl;
   }
   output <<inputFile << endl;
   size_t size = fileSize(inputFile);
   output << size << endl;
   
   string str;
   char c, charIndex;
   string str8Bits = "";
   ifstream input;
   input.open(inputFile.c_str());
   for (size_t i = 0; i < size; i++) {
      c = input.get();
      if (c < 0) str += (*_codeTable)[size_t(int(c) + 256)];
      else str += (*_codeTable)[size_t(c)];
      while (str.size() >= 8) {
         str8Bits = str.substr(0, 8);
         str = str.substr(8);
         charIndex = bitToChar(str8Bits);
         //cerr << str8Bits << " " << int(charIndex) << endl;
         output << charIndex;
      }
   }
   if (str.size()) {
      for (; str.size() < 8;)
         str = str + "0";
      charIndex = bitToChar(str);
      //cerr << str << " " << int(charIndex) << endl << endl;
      output << charIndex; 
   }
   input.close();
   output.close();
}
   
void Compressor::printCompressionInfo(const string& inputFile, const string& outputFile) 
{
   size_t m1 = fileSize(inputFile);
   size_t m2 = fileSize(outputFile);
   double ratio = m2;
   ratio = ratio * 100 / m1;
      
   cout << endl
        << "Original File Size   : " << m1 << " bytes" << endl
        << "Compressed File Size : " << m2 << " bytes" << endl
        << "Compression Ratio    : " << ratio << " %" << endl
        << endl;
}

bool Decompressor::decompressFile(const string& inputFile) 
{
   cout << "Decompressing File \"" << inputFile << "\" ..." << endl;
   ifstream input;
   input.open(inputFile.c_str());
   if (input == 0 || readCodeTable(input) == false) return false;
   _nodeTree.init(_codeTable);
   //_nodeTree.print();
   _root = _nodeTree.genTreeFromRoot();
   //_nodeTree.print();
   decoding(input);
   return true;
}

bool Decompressor::readCodeTable(ifstream& input) 
{
   for (size_t i = 0; i < 256; ++i)
      _codeTable->push_back("");
   string line, token;
   
   getline(input, line);
   size_t s = myStrGetTok(line, token);
   if (myStrNCmp("huff", token, 4) != 0) return false;
   myStrGetTok(line, token, s);
   int charNodeNum;
   if (myStrToInt(token, charNodeNum) == false) return false;
  
   for (size_t i = 0; i < size_t(charNodeNum); ++i) {
      if (getline(input, line) == 0) return false;
      int index;
      s = myStrGetTok(line, token);
      if (myStrToInt(token, index) == false) return false;
      myStrGetTok(line, token, s);
      (*_codeTable)[size_t(index)] = token;
   }
   return true;
}
   
void Decompressor::decoding(ifstream& input) 
{
   string str;
   getline(input, str);
   ofstream output;
   string outputFile = getFileName(str);
   output.open(outputFile.c_str());
   getline(input, str);
   int size;
   myStrToInt(str, size);
   
   char c, outputChar;
   Node* cursor = _root;
   str = "";
   for (size_t i = 0; i < size;) {
      if (str.size() == 0) {
         c = input.get();
         str = charToBit(c);
         //cerr << setw(4) << int(c) << " " << str << endl;
      }
      if (cursor->genOutputChar(str, outputChar, cursor) == true) {
         //cerr << charToBit(outputChar) << " " << outputChar << endl;
         ++i;
         cursor = _root;
         output << outputChar;
      }
   }
   input.close();
   output.close();
}


