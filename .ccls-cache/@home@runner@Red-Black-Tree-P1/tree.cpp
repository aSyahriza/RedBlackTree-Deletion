#include "tree.h"
#include <fstream>

Tree::Tree(){
  root = NULL;
  numOfNodes = 0;
}
Tree::~Tree(){
  delete root;
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
  recursePrint(root, NULL, 0);
}

void Tree::recursePrint(Node* current,Node* prev,int currentLevel){
  // Recurse into right child
  int newLevel = currentLevel + 1;
  if(currentLevel != totalLevels && current !=NULL){
    recursePrint(current->getRight(), current,newLevel);
  }
  /// Remove prev!=NULL to make spacing more accurate (but too spaced out)
  if(current==NULL&&prev!=NULL){
    if(currentLevel != totalLevels){
      recursePrint(NULL,current,newLevel);
    }
  }

  //Prints appropriate # of spaces
  for(int j = 0; j < currentLevel; j++){
    cout << "\t";
  }
  //Prints value
  if(current!=NULL){
    if(current->getValue()<1000){
      // Cout color 
      cout << current->getValue(); 
      if(current->getColor()==0){
        cout << "B" << endl;
      }
      else{
        cout << "R" << endl;
      }
    }
  }
  // Prints null pointers
  else if(prev!=NULL){
    cout << "N" << endl;
  }
  
  else{
    cout << endl;
  }
  

  //Traverse into left child
  if(currentLevel != totalLevels&&current!=NULL){
    recursePrint(current->getLeft(),current, newLevel);
  }

  // Remove prev!=NULL to make spacing more accurate (but too spaced out)
  if(current==NULL&&prev!=NULL){
    if(currentLevel != totalLevels){
      recursePrint(NULL,current,newLevel);
    }
  }

  
}

void Tree::add(int pValue){
  int count = 0;
  Node* newNode = new Node(pValue);
  Node* temp = root;
  // Iterate to the node that will become the parent of newNode
  while(true){
    if(temp != NULL){
      cout << "temp: " << temp->getValue() << endl;
    }
    if(numOfNodes == 0){
      root = newNode;
      numOfNodes++;
      newNode->setColor(0);
      break;
    }
    count++; 
    // Iterates through binary tree until it reaches where 
    // the new node should be
    if(temp->getValue()>=newNode->getValue()){
      if(temp->getLeft()!=NULL){
        temp=temp->getLeft();
        continue;
      }
      else{
        temp->setLeft(newNode);
        newNode->setParent(temp);
        numOfNodes++;
        break;
      }
    }
    else if(temp->getValue()<newNode->getValue()){
      if(temp->getRight()!=NULL){
        temp=temp->getRight();
        continue;
      }
      else{
        temp->setRight(newNode);
        newNode->setParent(temp);
        numOfNodes++;
        break;
      }
    }  
  }
  count++; 
  // Keeps track of the number of levels of tree
  if(count > totalLevels){
    totalLevels = count;
  }
  
  cout << "Count2: " << totalLevels << endl;
  

  
  fixReds(newNode);
  root->setColor(0);
  
  
  
  // This gonna be hella long

  // Recursive function to traverse or maybe use iteration idk
    
}  

void Tree::fixReds(Node* current){
  cout << "PK: " << current->getValue() << endl;
  
  // Returns if root or child of root
  if(current==root||current->getParent()==root){
    return;
  }
  cout << "PK Parent: " << current->getParent()->getValue() << endl;
  Node* tempParent = current->getParent();
  Node* tempGrandParent = current->getParent()->getParent();
  // If both parent and child are red
  if((current->getColor() == 1 && tempParent->getColor() == 1)){
    // If uncle is red too
    if((tempGrandParent->getRight()!=NULL && tempGrandParent->getLeft()!=NULL)&&(tempGrandParent->getRight()->getColor()==1 && tempGrandParent->getLeft()->getColor()==1)){
      tempGrandParent->setColor(1);
      tempGrandParent->getRight()->setColor(0);
      tempGrandParent->getLeft()->setColor(0);
      cout << "orange" << endl;
      // Checks if created another instance of consecutive reds
      rotate(current->getParent()->getParent(),0);
      
    }
    else{
      cout << "bean" << endl;
      print();
      rotate(current,0);
    }
   
    
    
    
  } 
  // Parent and child not red
  else{
    return;
  }
  
}


void Tree::rotate(Node* current, int recurseCount){
  if(current==root){
    cout << "1" << endl;
    return;
  }
  // Gotta do something. will figure out later
  if(current->getParent()==root){
    cout << "2" << endl; 
    return;
  }
  cout << "3" << endl;
  Node* tempGrandParent = current->getParent()->getParent();
  Node* tempParent = current->getParent();

  cout << "granny: " << tempGrandParent->getValue() << endl;
   cout << "pawpaw: " << tempParent->getValue() << endl;
  // 1: Left, 
  if(tempGrandParent->getLeft()==tempParent || recurseCount == 1){
     cout << "A" << endl;
    // 2: Left
    if(tempParent->getLeft()==current){
       cout << "B" << endl;
      // Still need to implement roots, look at doc and visualizer
      // Rotate Right
      tempGrandParent->setLeft(current);
      tempParent->setLeft(current->getRight());
      current->setRight(tempParent);
      // If second recursion
      if(recurseCount == 1){
        current->setColor(0);
        current->getLeft()->setColor(1);
      }          
    }
     // 2: Right
    else{
      // Rotate Left
      tempGrandParent->setRight(current);
      tempParent->setRight(current->getLeft());
      current->setLeft(tempParent);
      if(recurseCount == 0){
        rotate(current,1);
      }
      if(recurseCount == 1){
        current->setColor(0);
        current->getRight()->setColor(1);
      }
    }
  }
  // 1: Right
  else{
    // 2: Right
    if(tempParent->getRight()==current){
      // Still need to implement roots, look at doc and visualizer
      // Rotate Left
      tempGrandParent->setRight(current);
      tempParent->setRight(current->getLeft());
      current->setLeft(tempParent);
      return;
    } 
    // 2: Left
    else{
      tempGrandParent->setLeft(current);
      tempParent->setLeft(current->getRight());
      current->setRight(tempParent);
      if(recurseCount == 0){
        rotate(current,1);
      }
    }
  }
  return;
}
