#include "node.h"


class Tree {
public:
  Tree();
  ~Tree();
  void add(int);
  void addFile(char* fileName);
  void print();
  void recursePrint(Node*, int);

private:
  int totalLevels;
  Node* root;
  int numOfNodes = 0;



}