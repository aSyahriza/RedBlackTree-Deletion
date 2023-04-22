#include "tree.h"
#include <fstream>

Tree::Tree(){
  root = NULL;
  numOfNodes = 0;
}
Tree::~Tree(){
  delete root;
}
void Tree::add(int pValue){
  Node* newNode = new Node(pValue);
  Node* temp = root;
  // Iterate to the node that will become the parent of newNode
  while(true){
    if(temp->getValue()>=newNode->getValue()){
      if(temp->getRight()!=NULL){
        temp=temp->getRight();
      }
      else{
        break;
      }
    }
    else if(temp->getValue()<newNode->getValue()){
      if(temp->getLeft()!=NULL){
        temp=temp->getLeft();
      }
      else{
        break;
      }
    }
  }

  // Add newNode to the tree
  if(temp->getValue()>=newNode->getValue()){
    temp->setLeft(newNode);
  }
  else if(temp->getValue()<newNode->getValue()){
    temp->setRight(newNode);
  }

  
  
  
  // This gonna be hella long

  // Recursive function to traverse or maybe use iteration idk
    
}  
void Tree::addFile(char* fileName){
  // Checks if file exists
  ifstream tempFile;
  tempFile.open(fileName);
  
  if(tempFile){
    // Reads through every value in file, adds to heap
    cout << "File found." << endl;
    ifstream MyReadFile(fileName);
    int temp;
    while (MyReadFile >> temp){
      if(temp > 999){
        continue;
      }
      add(temp);
    }
    cout << "Values have been added." << endl;
  }
  else{
    cout << "Unable to find file" << endl;
  }
    
}  
void Tree::print(){
  if(numOfNodes==0){
    cout <<"List is empty." << "\n" << endl;
    return;
  }
  recursePrint(root, 0);
}

void Tree::recursePrint(Node* current,int currentLevel){
  // Recurse into right child
  int newLevel = currentLevel + 1;
  if(currentLevel != totalLevels&& current!=NULL){
    recursePrint(current->getRight(), newLevel);
  }
  // Causes print to be more accurately spaced, but also becomes too spaced out in some cases
  /*if(current==NULL){
    if(currentLevel != totalLevels){
      recursePrint(NULL,newLevel);
    }
  }*/

  //Prints appropriate # of spaces
  for(int j = 0; j < currentLevel; j++){
    cout << "\t";
  }
  //Prints value
  if(current!=NULL){
    if(current->getValue()<1000)
      cout << current->getValue()<< endl;
  }
  else{
    cout << endl;
  }

  //Traverse into left child
  if(currentLevel != totalLevels&&current!=NULL){
    recursePrint(current->getLeft(), newLevel);
  }
  /*
  if(current==NULL){
    if(currentLevel != totalLevels){
      recursePrint(NULL,newLevel);
    }
  }*/

  
}

