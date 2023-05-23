#include "node.h"

using namespace std;


class Tree {
public:
  Tree();
  ~Tree();
  void add(int);
  void addFile(char* fileName);
  void deleteNode(int);
  void print();
  void recursePrint(Node*, Node*, int);
  void fixReds(Node*);
  void rotate(Node*,int, int);
  void testFunction();
  void blackDeletion(Node* uNode,Node* sNode,Node* pNode,int count);
  bool searchTree(Node* current, int num);
  Node* getRoot();

private:
  int totalLevels = 0;
  Node* root;
  int numOfNodes = 0;



};