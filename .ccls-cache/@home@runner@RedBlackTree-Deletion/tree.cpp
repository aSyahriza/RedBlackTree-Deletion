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
    cout << "Values have been added." << "\n" << endl;
  }
  else{
    cout << "Unable to find file" << endl;
  }
    
}  
void Tree::print(){
  if(numOfNodes==0){
    cout <<"Tree is empty." << "\n" << endl;
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
  
  

  // Finds if red black rule has just been broken, fixes
  fixReds(newNode);
  // Root is always black
  root->setColor(0);
}  

void Tree::fixReds(Node* current){
  
  // Returns if root or child of root
  if(current==root||current->getParent()==root){
    return;
  }
  Node* tempParent = current->getParent();
  Node* tempGrandParent = current->getParent()->getParent();
  // If both parent and child are red
  if((current->getColor() == 1 && tempParent->getColor() == 1)){
    // If uncle is red too
    if((tempGrandParent->getRight()!=NULL && tempGrandParent->getLeft()!=NULL)&&(tempGrandParent->getRight()->getColor()==1 && tempGrandParent->getLeft()->getColor()==1)){
      // Pushes down blackness from grandparent
      tempGrandParent->setColor(1);
      tempGrandParent->getRight()->setColor(0);
      tempGrandParent->getLeft()->setColor(0);
      // Checks if created another instance of consecutive reds
      fixReds(current->getParent()->getParent());
      
    }
    // Consecutive reds, but uncle is black or NULL
    else{
    
      // Check which rotations should be done
      
      if(tempParent->getLeft()==current){
        // Parent is left child, current is left child
        // Right rotation
        if(tempGrandParent->getLeft()==tempParent){
          rotate(current->getParent(),0,0);
        }
        // Parent is left child, current is right child
        // Right, then left rotation
        else{
          rotate(current,0,1);
        }
      }
      else{
        // Parent is right child, current is right child
        // Left rotation
        if(tempGrandParent->getRight()==tempParent){
          rotate(current->getParent(),0,2);
        }
        // Parent is right child, current is left child
        // Left, then right rotation
        else{
          rotate(current,0,3);
        }
      }
    }
  } 
  // Parent and child not red
  else{
    return;
  }
  
}


void Tree::rotate(Node* current, int recurseCount, int rotationDir){
  // Rotation Dir:
  // Left: 0,1
  // Left, then right: 1
  // Right: 2, 3
  // Right, then left: 3
  
  // 0 = left, 
  // 1 = right
  bool willBeRoot = false;
  bool grandparentDirection;
  
  if(current == NULL){
    return;
  }
  
  if(current==root){
    return;
  }

  Node* tempGrandParent = current->getParent()->getParent();
  Node* tempParent = current->getParent();

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
  }
  // Checks if current will become the new root
  else{
    willBeRoot = true;
  }
  
  
  // 1: Current is left child
  if(rotationDir < 2){
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
    tempParent->setLeft(current->getRight());
    current->setRight(tempParent);
    if(tempParent->getLeft()!=NULL){
      current->getRight()->setParent(tempParent);
    }
    tempParent->setParent(current);
    current->setColor(0);
    tempParent->setColor(1);
    // Recurses if extra rotation is necessary
    if(rotationDir == 1){
      rotate(current,0,2);
    }
    return;
  }
  // 2: Current is right child
  else{
    // Rotate Left
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
    tempParent->setRight(current->getLeft());
    current->setLeft(tempParent);
    if(tempParent->getRight()!=NULL){
      tempParent->getRight()->setParent(tempParent);
    }
    tempParent->setParent(current);
    current->setColor(0);
    tempParent->setColor(1);
    // Recurses if extra rotation is necessary
    if(rotationDir == 3){
      rotate(current,0,0);
    }
    return;
  }
  return;
}

bool Tree::searchTree(Node* current, int num){
  if(numOfNodes == 0){
    cout << "List is empty" << "\n" << endl;
    return false;
  }
  // If the node has not been found
  if(current==NULL){
    return false;
  }
  if(current->getValue() == num){
    return true;
  }
    // traverse into left child
  else if(num<=current->getValue()){
    return searchTree(current->getLeft(),num);
  }
    // traverse into right child
  else if(num>current->getValue()){
    return searchTree(current->getRight(),num);
  }
}

Node* Tree::getRoot(){
  return root;
}


void Tree::deleteNode(int valueToDelete){
  Node* temp = root;
  Node* uNode;
  Node* pNode;
  Node* sNode;
  bool toDeleteRoot;

  // If not in tree
  if(!searchTree(root,valueToDelete)){
    cout << "Value is not in tree." << endl;
    return;
  }
  cout << "1" << endl;
  // If deleting root
  if(root->getValue()==valueToDelete){
    toDeleteRoot = true;
  }
  
  cout << "2" << endl;
  // Find value of the node
  while(temp->getValue()!=valueToDelete){
    cout << "currents value: " << temp->getValue() << endl;
    cout << "3" << endl;
    if(temp==NULL){
      cout << "Value is not in tree" << endl;
      return; 
    }
    if(temp->getValue()>=valueToDelete){
      temp=temp->getLeft();
    }
    else{
      temp=temp->getRight();
    }
  }
  // Temp has two children
  if(temp->getLeft()!=NULL&&temp->getRight()!=NULL){
    cout << "4" << endl;
    Node* successor = temp->getRight();
    while(successor->getLeft()!=NULL){
      successor = successor->getLeft();
    }
    // Swaps the values of the node to delete with its in order successor 
    int tempValue = temp->getValue();
    temp->setValue(successor->getValue());
    successor->setValue(tempValue);
    

    temp = successor;
    cout << "temp value: " <<  temp->getValue();
    cout << "temp parents value: " << temp->getParent()->getValue();
    
    print();
    // Need to swap successor and temp, idk how yet
    //  
  }

  pNode = temp->getParent();
  
  // If temp has no children
  // U is null
  if(temp->getRight()==NULL&&temp->getLeft()==NULL){
    cout << "5" << endl;
    ///////////////////// Can I replace this with uNode = NULL? 
    // Setting U as the node that replaces temp
    uNode = NULL;
    
  }
  // If temp has one child
  // U is a value
  else if(temp->getRight()==NULL || temp->getLeft()==NULL){
    // Temp is the left child 
    if(temp->getLeft()!=NULL){
      uNode = temp->getLeft();
    }
    else{
      uNode = temp->getRight();
    }
  }
  cout << "temp value: " << temp->getValue() << endl;
  if(uNode!=NULL){
    cout << "uNode value: " << uNode->getValue() << endl;  
  }
  else{
    cout << "UNode is null" << endl;
  }
  

  // Replaces V(temp) with U
  if(toDeleteRoot){
    
  }
  if(pNode->getLeft()==temp){
    cout << "ASKJ" << endl;
    pNode->setLeft(uNode);
    sNode = pNode->getRight();
    cout << "DHSAD1" << endl;
  }
  else{
    pNode->setRight(uNode);
    cout << "powwl" << endl;
    sNode = pNode->getLeft();
    
  }
  if(sNode!=NULL){
    cout << "seetlejuice: " << sNode->getValue() << endl;
  }
  cout << "peetlejuice: " << pNode->getValue() << endl;
  
  if(uNode!=NULL){
    uNode->setParent(pNode);  
  }
  
  cout << "DHSAD2" << endl;
  // If either U or V is red
  if(temp->getColor()==1||uNode!=NULL && uNode->getColor()==1){
    cout << "sladkl" << endl;
    if(uNode!=NULL){ 
      uNode->setColor(0);
    }
  }
  // both are black
  else{
    cout << "DHSAD3" << endl;
    if(uNode!=NULL){
      uNode->setColor(-1);
    }

    
    
    blackDeletion(uNode, sNode, pNode);
  }
  //if(temp->get)
}

void Tree::blackDeletion(Node *uNode, Node *sNode, Node *pNode){

  bool toBecomeRoot;

  if(pNode==root){
    toBecomeRoot = true;
  }
  
  if(uNode!=NULL){
    cout << "uNode valueeee: " << uNode->getValue() << endl;
  }
  if(sNode!=NULL){
    cout << "sNode valueeee: " << sNode->getValue() << endl;
  }
  if(pNode!=NULL){
    cout << "pNode valueeee: " << pNode->getValue() << endl;
  }

  

  sNode->getLeft()==nullptr? 'b' : sNode->getLeft()->getColor();
  // Need to have return cases
  if(uNode!=NULL &&uNode->getColor()==1){
    return;
  }
  Node* rNode;
  // If sibling is black and has a red child
  cout << "AHHH AHHHH" << endl;
  print();
  // return;
  if((sNode->getColor()==0)&&((sNode->getLeft()!=NULL&&sNode->getLeft()->getColor()==1)||sNode->getRight()!=NULL&&sNode->getRight()->getColor()==1)){
    // ___, then left
    cout << "1" << endl;
    if(sNode->getLeft()!=NULL&&sNode->getLeft()->getColor()==1){
      rNode = sNode->getLeft();
      cout << "1A" << endl;
      // Left, then left
      if(pNode->getLeft()==sNode){
        cout << "1AI" << endl;
        rotate(sNode,0,0);
      }
      // Right, then left
      else{
        cout << "1AII" << endl;
        rotate(rNode,0,3);
      }
      sNode->setColor(1);
      pNode->setColor(0);
      sNode->getLeft()->setColor(0);
      return;
    }
    // ___, then right
    else{
      cout << "1B" << endl;
      rNode = sNode->getRight();
      // Left, then right
      if(pNode->getLeft()==sNode){
        cout << "1BI" << endl;
        rotate(rNode,0,1);
      }
      // Right, then right
      else{
        cout << "1BII" << endl;
        rotate(sNode,0,2);
      }
      sNode->setColor(1);
      pNode->setColor(0);
      sNode->getRight()->setColor(0);
      return;
    }    
  }
  // If S is black and its nodes are black
  else if((sNode->getColor()==0)){
    cout << "2" << endl;
    if(uNode!=NULL){
      uNode->setColor(0);  
    }
    sNode->setColor(1);
    if(pNode->getColor()==1){
      cout << "2A" << endl;
      pNode->setColor(0);
    }
    else if(pNode->getColor()==0){
      cout << "2B" << endl;
      pNode->setColor(-1);
      // return;
      if(pNode->getParent()->getLeft()==pNode){
        cout << "2BI" << endl;
        blackDeletion(pNode,pNode->getParent()->getRight(),pNode->getParent());
        return;
      }
      else{
        cout << "2BII" << endl;
        blackDeletion(pNode,pNode->getParent()->getLeft(),pNode->getParent());
        return;
      }
    }
    // Extraneous
    print();
    return;
    ///
  }
  print();
  cout << "0234800394" << endl;
  // If S is red
  if(sNode->getColor()==1){
    cout << "3" << endl;
    // If sNode is the left sibling
    if(pNode->getLeft()==sNode){
      cout << "3A" << endl;
      rotate(sNode,0,0);
    }
    // If sNode is the right sibling
    else{
      cout << "3B" << endl;
      rotate(sNode,0,2);
    }
    blackDeletion(uNode, pNode, sNode);
  }
}

void Tree::testFunction(){
  add(10);
  cout << root->getValue() << endl;
  if(root->getValue() == 3|| root->getLeft()==NULL ){
    cout << "!M!!MM!"<< endl;
  }
}