#include "node.h"

  // 0 = black
  // 1 = red
Node::Node(){
  value = 0;
  color = 0;
  left = NULL;
  right = NULL;
  parent = NULL;
}
  // 0 = black
  // 1 = red
Node::Node(int pValue){
  value = pValue;
  color = 1;
  left = NULL;
  right = NULL;
  parent = NULL;
}
Node::~Node(){
  left = NULL;
  right = NULL;
  parent = NULL;
  delete left;
  delete right;
  delete parent;
}
void Node::setColor(int pColor){
  color = pColor;
}
void Node::setLeft(Node* pLeft){
  left = pLeft;
}
void Node::setRight(Node* pRight){
  right = pRight;
}
void Node::setParent(Node* pParent){
  parent = pParent;
}
int Node::getValue(){
  return value;
}
int Node::getColor(){
  return color;
}
Node* Node::getLeft(){
    return left;
  }
  Node* Node::getRight(){
    return right;
  }
  Node* Node::getParent(){
    return parent;
  }


/*





*/