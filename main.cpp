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

  cout << "Enter ADD, ADD BY FILE, PRINT, or QUIT" << endl;
  cout << "Try: 170, 40, 45" << endl;
  cout << "Try: 170" << endl;
  cout << "\n" << endl;

  char* name = new char[20];
  strcpy(name,"file.txt");
  myTree.addFile(name);
  
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
      cout << "\n";
      
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