#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
 
class Node;
class NodeTree;

typedef vector<Node*> NodeList;
typedef vector<string> CodeTable;

bool myNodeCompare(Node*, Node*);
void myTwoOutOfThree(Node*&, Node*&, Node*&); 

class Node
{
   friend class NodeTree;
public:
   Node(int ch, string str) : _charName(ch), _count(0), _left(0), _right(0), _parent(0), _code(str) {}
   Node(size_t s, Node* l, Node* r) : _charName(0), _count(s), _left(l), _right(r), _parent(0), _code("") {}
   
   ~Node() {};
   
   size_t getCount() { return _count; }
   friend ostream& operator<<(ostream& out, const Node n) {
      string str;
      str += n._charName;
      out << setw(3) << n._charName << " \'" 
          << ((n._charName == 10) ? "\\n" : str) 
          << "\' " << n._count << " " << n._code << endl;
      return out;
   }
   
   void genCode();
   void genTreeFromRoot(NodeList*& tree);
   bool genOutputChar(string& str, char& outputChar, Node*& n);
private:
   int          _charName;
   size_t       _count;
   Node*        _left;
   Node*        _right;
   Node*        _parent;
   string       _code;
};

class NodeTree
{
   friend class Node;
public:
   NodeTree() { 
      _tree = new NodeList; 
      _charNodeNum = 0; 
   }
   ~NodeTree() { clear(); }

   void clear() {
      for (size_t i = 0; i < _tree->size(); ++i)
         delete (*_tree)[i];
      _tree->clear();
      delete _tree;
      _tree = 0;
   }
   
   //for Compressor
   void init(ifstream& input);
   void genTreeFromLeaf(size_t nodeNum);
   void genCodeTable(CodeTable* table);
   
   //for Decompressor
   void init(const CodeTable* table);
   Node* genTreeFromRoot();
   
   Node* operator[](const size_t i) { return (*_tree)[i]; }
   size_t size() const { return _tree->size(); }
   size_t getCharNodeNum() const { return _charNodeNum; }

   void print() const {
      for (size_t i = 0; i < size(); ++i)
         cout << (*(*_tree)[i]);
   }

private:
   NodeList*  _tree;
   size_t     _charNodeNum;
   
   void reorganize();
};


