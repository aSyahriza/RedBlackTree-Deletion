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

void Node::setValue(int pValue){
  value = pValue;
}
int Node::getValue(){
  return value;
}
int Node::getColor(){
  return color;
}

int Node::getType(Node* current){
  if(current==NULL){
    return 2;
  }
  else if(current->getColor()==0){
    return 0;
  }
  else if(current->getColor()==1){
    return 1;
  }
  else{
    return -1;
  }
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