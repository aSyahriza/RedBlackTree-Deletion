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
  // Figure out ehat to do if grandchild of root
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
      print();
      if(current->getValue()==45){
        cout << "current1: " << current->getValue() << endl;
        cout << "current2: " << current->getParent()->getValue() << endl;
        cout << "current3: " << current->getParent()->getParent()->getValue() << endl;
        cout << "current4: " << current->getParent()->getParent()->getParent()->getValue() << endl;
      }
      // Checks if created another instance of consecutive reds
      fixReds(current->getParent()->getParent());
      
    }
    else{
      cout << "bean" << endl;
      print();
      rotate(current->getParent(),0);
    }
   
    
    
    
  } 
  // Parent and child not red
  else{
    return;
  }
  
}


void Tree::rotate(Node* current, int recurseCount){
  // 0 = left, 
  // 1 = right
  bool willBeRoot = false;
  bool grandparentDirection;
  bool childDirection;
  
  cout << "m"<< endl;
  if(current == NULL){
    return;
  }
  cout << "current"<<  current->getValue() <<endl;
  
  cout << "h" << endl;
  if(current->getColor()==0){
    return;
  }
  if(current->getRight()!=NULL){
    if(current->getRight()->getColor()==1){
      childDirection = 1;
    }
  }
  else if(current->getLeft()!=NULL){
    if(current->getLeft()->getColor()==1){
      childDirection = 0;
    }
  }
  else{
    return;
  }
  
  cout << "jink" << endl;
  
  if(current==root){
    cout << "1" << endl;
    return;
  }
  // Gotta do something. will figure out later
  
  cout << "3" << endl;

  Node* tempGrandParent = current->getParent()->getParent();
  Node* tempParent = current->getParent();

  
  cout << "current: " << current->getValue() << endl;
   cout << "pawpaw: " << tempParent->getValue() << endl;

  // If there will not be issues with root
  if(current->getParent()!=root){
    
   // Parent is right
    if(tempGrandParent->getRight()==tempParent){
      grandparentDirection = 1;
    }
    // Parent is left
    else{
      grandparentDirection = 0;
    }
    cout << "granny: " << tempGrandParent->getValue() << endl;
  }
  else{
    willBeRoot = true;
  }
  // 1: Left, 
  if(tempParent->getLeft()==current || recurseCount == 1){
     cout << "A" << endl;
    // 2: Left
    if(current->getLeft()->getColor()==1){
       cout << "B" << endl;
      // Still need to implement roots, look at doc and visualizer
      // Rotate Right
      if(!willBeRoot){
        if(!grandparentDirection){
          tempGrandParent->setLeft(current);      
        }
        else{
          tempGrandParent->setRight(current);
        }
        current->setParent(tempGrandParent);
      }
      else{
        root = current;
      }
      cout << "Martin" << endl;
      tempParent->setLeft(current->getRight());
      cout << "Baby keem" << endl;
      current->setRight(tempParent);
      cout << "Jones" << endl;
      if(tempParent->getLeft()!=NULL){
        current->getRight()->setParent(tempParent);
      }
      cout << "Klod" << endl;
      tempParent->setParent(current);
      cout << "!!!Yea" << endl;
      current->setColor(0);
      tempParent->setColor(1);
      return;
      // If second recursion
      // This code is weird
      /*
      if(recurseCount == 1){
        current->setColor(0);
        current->getLeft()->setColor(1);
      }      
      */
    }
     // 2: Right
     // Needs work
    else{
      
      // Rotate Left
      tempGrandParent->setRight(current);
      current->setParent(tempGrandParent);
      tempParent->setRight(current->getLeft());
      if(tempParent->getRight()!=NULL){
        current->getLeft()->setParent(tempParent);
      }
      current->setLeft(tempParent);
      tempParent->setParent(current);
      
      if(recurseCount == 0){
        rotate(current,1);
      }
      // This code is weird
      if(recurseCount == 1){
        current->setColor(0);
        current->getRight()->setColor(1);
      }
    }
  }
  // 1: Right
  else{
    cout << "C" << endl;
    // 2: Right
    if(current->getRight()->getColor()==1){
      cout << "D" << endl;
      // Still need to implement roots, look at doc and visualizer
      // Rotate Left
      if(!willBeRoot){
        cout << "Meehic "<< endl;
        if(!grandparentDirection){
          tempGrandParent->setLeft(current);
        }
        else{
          tempGrandParent->setRight(current);
        }
        current->setParent(tempGrandParent);
      }
      else{
        cout << "beeno "<< endl;
        root = current;
      }
      cout << "jeans" << endl;
      tempParent->setRight(current->getLeft());
      cout << "naj" << endl;
      current->setLeft(tempParent);
      if(tempParent->getRight()!=NULL){
        tempParent->getRight()->setParent(tempParent);
      }
      tempParent->setParent(current);
      current->setColor(0);
      tempParent->setColor(1);
      cout << "ham" << endl;
      return;
    } 
    // 2: Left
    else{
      cout << "E" << endl;
      tempGrandParent->setLeft(current);
      current->setParent(tempGrandParent);
      tempParent->setLeft(current->getRight());
      if(tempParent->getLeft()!=NULL){
        current->getRight()->setParent(tempParent);
      }
      current->setRight(tempParent);
      tempParent->setParent(current);
      if(recurseCount == 0){
        rotate(current,1);
      }
    }
  }
  return;
}
