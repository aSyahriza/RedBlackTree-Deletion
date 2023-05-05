#include "node.h"

using namespace std;


class Tree {
public:
  Tree();
  ~Tree();
  void add(int);
  void addFile(char* fileName);
  void print();
  void recursePrint(Node*, Node*, int);
  void fixReds(Node*);
  void rotate(Node*,int, int);

private:
  int totalLevels = 0;
  Node* root;
  int numOfNodes = 0;



};