/*
* Author: Allam Syahriza
* Date: 5/23/23
* Project: Red Black Tree Deletion
* This program creates a Red-Black binary tree of values, 
* with the ability to insert and delete values.
*/

#include <iostream>
#include <cstring>

#include <vector> 

#include "tree.h"

using namespace std;

int main() {

  bool loop = true;
  Tree myTree;
  char command[20];
  char* fileName = new char[20];
  
  
  cout << "Enter ADD, ADD BY FILE, DELETE, PRINT, SEARCH, or QUIT" << endl;
  cout << "\n" << endl;


  
  while(loop){
    cin.get(command,20,'\n');
    cin.clear();
    cin.ignore(99999,'\n');
    
    // Checks if the user wants to ADD a single number to the heap
    if(strcmp(command, "ADD") == 0){
      cout << "Enter a number, within a range of 1-999)" << endl;
      int num;
      cin >> num;
      myTree.add(num);
      cout << "Value has been added." << endl;
      cout << "\n";
    }
    
    // Checks if the user wants to read in a file of numbers seperated by a space
    if(strcmp(command, "ADD BY FILE") == 0){
      cout << "Enter a file name: " << endl;
      cin.get(fileName,20,'\n');
      cin.clear();
      cin.ignore(99999,'\n');
      myTree.addFile(fileName); 
    }

    if(strcmp(command, "DELETE") == 0){
      cout << "Enter a number to delete: "<< endl;
      int num;
      cin >> num;
      myTree.deleteNode(num);
      cout << "\n"; 
    }
    
    if(strcmp(command, "SEARCH") == 0){
      cout << "Enter a number to search: " << endl;
      int num;
      cin >> num;
      if(myTree.searchTree(myTree.getRoot(),num)){
        cout << "Number found! " << endl;
      }
      else{
        cout << "Unable to find number. " << endl;
      }
      cout << endl;
    }
   
    // Check if the user wants to print the tree
    if(strcmp(command, "PRINT") == 0){
      myTree.print();
      cout << endl;
    }

    // Quit
    if(strcmp(command, "QUIT") == 0){
      loop = false;
    }
  }  
  
  cout << "Program ended. " << endl;
  
}