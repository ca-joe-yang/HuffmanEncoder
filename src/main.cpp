#include <cstdlib>
#include <cstring>
#include "myHuffman.h"
#include "util.h"

using namespace std;

static void usage()
{
   cout << "Usage: Huffman < (-Compress < inputFile > < outputFile >)" << endl
        << "                    | (-Decompress < inputFile >) >" << endl;
}

static void myExit()
{
   usage();
   exit(-1);
}

int main(int argc, char** argv) 
{
   if (argc == 4) {
      if (myStrNCmp("-Compress", argv[1], 2) == 0) {
         // -Compress <inputFile> <outputFile>
         Compressor* compressor = new Compressor();
         if (compressor->compressFile(argv[2], argv[3]) == false)
            cerr << "Error: Cannot compress file \"" << argv[2] << "\" !!" << endl;
         else cout << "Compression Success" << endl;
         return 0;
      }
      cerr << "Error: Unknown argument \"" << argv[1] << "\" !!" << endl;
      myExit();
   }
   else if (argc == 3) {
      if (myStrNCmp("-Decompress", argv[1], 2) == 0) {
         // -Decompress <encoded> 
         Decompressor* decompressor = new Decompressor();
         if (decompressor->decompressFile(argv[2]) == false)
            cerr << "Error: Cannot decompress file \"" << argv[2] << "\" !!" << endl;
         else cout << "Decompression Success." << endl;
         return 0;
      }
      cerr << "Error: Unknown argument \"" << argv[1] << "\" !!" << endl;
      myExit();
   }
   cerr << "Error: Illegal number of argument (" << argc <<") !!" << endl;
   myExit();
}

