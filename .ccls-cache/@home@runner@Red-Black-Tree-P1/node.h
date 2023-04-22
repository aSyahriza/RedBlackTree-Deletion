#include <iostream>

using namespace std;

class Node{
public:
  Node();
  Node(int pValue);
  ~Node();
  void setColor(int );
  void setLeft(Node*);
  void setRight(Node*);
  void setParent(Node*);
  int getValue();
  int getColor();
  Node* getLeft();
  Node* getRight();
  Node* getParent();

  
private:
  // 0 = black
  // 1 = red
  int value;
  int color;
  Node* left;
  Node* right;
  Node* parent;
}