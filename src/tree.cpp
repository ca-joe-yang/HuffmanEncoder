#include "tree.h"
#include "util.h"

using namespace std;

void Node::genCode() 
{
   if (_left != 0) {
      _left->_code = _code + "0";
      _left->genCode();
   }
   if (_right != 0) {
      _right->_code = _code + "1";
      _right->genCode();
   }
}

void Node::genTreeFromRoot(NodeList*& tree) 
{
   if (_charName != -1) return;
   string leftCode = _code + "0";
   string rightCode = _code + "1";
   for (size_t i = 0; i < tree->size(); ++i) {
      Node* n = (*tree)[i];
      if (n->_code == leftCode) {
         _left = n;
         n->_parent = this;
      }
      else if (n->_code == rightCode) {
         _right = n;
         n->_parent = this;
      }
      if (_left != 0 && _right != 0) break;
   }
   if (_left == 0) {
      Node* left = new Node(-1, leftCode);
      _left = left;
      left->_parent = this;
      tree->push_back(left);
   }
   if (_right == 0) {
      Node* right = new Node(-1, rightCode);
      _right = right;
      right->_parent = this;
      tree->push_back(right);
   }
   //cerr << _charName << " " << _code << endl;
   _left->genTreeFromRoot(tree);
   _right->genTreeFromRoot(tree);
}

bool Node::genOutputChar(string& str, char& outputChar, Node*& n) 
{
   if (str[0] == '0') {
      n = _left;
   }
   else if (str[0] == '1') {
      n = _right;
   }
   str = str.substr(1);
   if (n->_left == 0 || n->_right == 0) {
      outputChar = char(n->_charName); 
      return true;
   }
   else return false;
}

void NodeTree::init(ifstream& input) 
{
   for (int i = 0; i < 256; ++i) {
      Node* n = new Node(i, "");
      _tree->push_back(n);
   }
   while(true) {
      char c = input.get();
      if (c >= 0) (*_tree)[size_t(c)]->_count ++;
      else (*_tree)[size_t(256 + c)]->_count ++;
      if (c == EOF) break;
   }
   reorganize();
}
 
void NodeTree::init(const CodeTable* table) 
{
   for (size_t i = 0; i < table->size(); ++i) {
      if ((*table)[i] != "") {
         Node* n = new Node(i, (*table)[i]);
         _tree->push_back(n);
         _charNodeNum ++;
      }
   }
}

void NodeTree::reorganize() 
{
   sort(_tree->begin(), _tree->end(), myNodeCompare);
   size_t zeroTerm = 0;
   for (; (*_tree)[zeroTerm]->_count == 0; ++zeroTerm);
   NodeList* newTree = new NodeList;
   for (size_t i = zeroTerm; i < 256; ++i)
      newTree->push_back((*_tree)[i]);
   delete _tree;
   _tree = newTree;
   _charNodeNum = size();
   //print();
}

void NodeTree::genTreeFromLeaf(size_t nodeNum) 
{
   if (nodeNum == 1) return;
   size_t i = 0;
   for (; (*_tree)[i]->_parent != 0; ++i);
   Node* n1 = (*_tree)[i++];
   for (; (*_tree)[i]->_parent != 0; ++i);
   Node* n2 = (*_tree)[i++];
   for (size_t j = i; j < size(); ++j) {
      Node* n3 = (*_tree)[j];
      if (n3->_parent == 0)
         myTwoOutOfThree(n1, n2, n3);
   }
   size_t newCount = n1->_count + n2->_count;
   Node* n = new Node(newCount, n1, n2);
   n1->_parent = n2->_parent = n;
   _tree->push_back(n);
   nodeNum --;
   genTreeFromLeaf(nodeNum);
}

Node* NodeTree::genTreeFromRoot() 
{
   Node* root = new Node(-1, "");
   _tree->push_back(root);
   root->genTreeFromRoot(_tree);
   return root;
}

void NodeTree::genCodeTable(CodeTable* table) 
{
   if (table->size()) table->clear();
   for (size_t i = 0; i < 256; ++i)
      table->push_back("");
   Node* root = (*_tree)[size() - 1];
   root->genCode();
   for (size_t i = 0; i < _charNodeNum; ++i) {
      int index = (*_tree)[i]->_charName;
      (*table)[size_t(index)] = (*_tree)[i]->_code;
   }
}

bool myNodeCompare(Node* n1, Node* n2) 
{
   return (n1->getCount() < n2->getCount()); 
}

void myTwoOutOfThree(Node*& n1, Node*& n2, Node*& n3) 
{
   if (n3->getCount() < n2->getCount())
      if (n3->getCount() < n1->getCount())
         if (n1->getCount() < n2->getCount())
            n2 = n3;
         else 
            n1 = n3;
      else
         n2 = n3;
   else if (n3->getCount() < n1->getCount())
      n1 = n3;
}

