///////////////////////////////////////////////////////////////////
//
// Author:           Aodhan Shaw
// Email:            aodhanshaw@gmail.com
// Label:            Program 1
// Title:            Program 01 - Array Based Stack
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//       Overview of a class implementing an array based stack
//
//
///////////////////////////////////////////////////////////////////

// included libraries
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */

class ArrayStack{
private:
  int *A;           // pointer to array of int's
  int size;         // current max stack size
  int top;          // top of stack 
  int maxSize = 0;  // static variable to keep track of max size
  int resize = 0;   // keeps track of times resized
  int numPops = 0;  // keeps track of number of pops
  int numPushs = 0; // keeps track of number of pushs
  double tooFullThresh;
  double tooEmptyThresh;
  double enlargeThresh;
  double shrinkThresh;

public:

 /**
  * ArrayStack
  * 
  * Description:
  *     Default Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */

  ArrayStack(){
    size = 10;
    resize = 0;
    A = new int[size];
    top = -1;
    tooFullThresh = .85;
    tooEmptyThresh = .15;
    enlargeThresh = 2.0;
    shrinkThresh = .5;
  }

 /**
  * ArrayStack
  * 
  * Description:
  *      Constructor with params
  * 
  * Params:
  *     - double tooFull, tooEmpty, enlarge, shrink
  * 
  * Returns:
  *     N/A
  */

  ArrayStack(double tooFull, double tooEmpty, double enlarge, double shrink){
    size = 10;
    resize = 0;
    A = new int[size];
    top = -1;
    tooFullThresh = tooFull;
    tooEmptyThresh = tooEmpty;
    enlargeThresh = enlarge;
    shrinkThresh = shrink;
  }

 /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */

  bool Empty(){
    return (top <= -1);
  }
  
 /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */

  bool Full(){
    return (top >= size-1);
  }

 /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */

  int Peek(){
    if(!Empty()){
      return A[top];
    }
    
    return -99; // some sentinel value
                
  }

 /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */

  int Pop(){
    numPops++;
    if(FindRatio() <= getTooEmptyThresh()){
      ContainerShrink();
    }

    if(!Empty()){
      return A[--top];
    }
    else{
      return -99999;
    }
    
  }

 /**
  * Public void: Print
  * 
  * Description:
  *      Prints final data
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */

  void Print(){
    cout << "##########################################" << endl;
    cout << "   Assignment 4 - Resizing the stack" << endl;
    cout << "   CMPS 3013                        " << endl;
    cout << "   Aodhan Shaw                      " << endl << endl;
    cout << "   Config Params:                   " << endl;
    cout << "     Full Threshold: " << getTooFullThresh() << endl;
    cout << "     Shrink Threshold: " << getTooEmptyThresh() << endl;
    cout << "     Grow Ratio: " << getEnlargeThresh() << endl;
    cout << "     Shrink Ratio: " << getShrinkThresh() << endl << endl;
    cout << "   Processed " << (numPops + numPushs) << " commands" << endl << endl;
    cout << "   Max Stack Size: " << maxSize << endl;
    cout << "   End Stack Size: " << size << endl;
    cout << "   Stack Resized: " << resize << " times" << endl << endl;
    cout << "##########################################" << endl << endl;

    cout << "+------------+" << endl;
    cout << "Stack : \n";
    for(int i=0;i<=top;i++){
      cout << A[i] << endl;
    }
    cout << "+------------+";
    cout<<endl;
  } 

 /**
  * Public void: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      void
  */

  void Push(int x){
    numPushs++;
    if(FindRatio() >= getTooFullThresh()){
      ContainerGrow();
      A[++top] = x;
    }
    else{
      A[++top] =x;
    }
  }

 /**
  * Public void: ContainerGrow
  * 
  * Description:
  *      Resizes the container for the stack by enlarging
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */

  void ContainerGrow(){
    int newSize = size * getEnlargeThresh();       // increase size of original
    int *B = new int[newSize];  // allocate new memory

    for(int i=0;i<=top;i++){    // copy values to new array
      B[i] = A[i];
    }

    delete [] A;                // delete old array

    size = newSize;             // save new size
    
    if (size >= maxSize){
      maxSize = size;
    }

    A = B;                      // reset array pointer
    resize++;
  }

   /**
  * Public void: ContainerShrink
  * 
  * Description:
  *      Resizes the container for the stack by shrinking
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */

  void ContainerShrink(){
    if(size <= 10){
      return;
    }
    int newSize = size * getShrinkThresh();

    int *B = new int[newSize];    // allocating space

    for (int i=0; i <= top; i++){ // copying values
      B[i] = A[i];
    }

    delete [] A;                  // erasing old array

    size = newSize;               
    
    A = B;
    resize++;                      
  }

  /**
  * Public double: FindRatio
  * 
  * Description:
  *      devides top + 1 by the size to find
  *      how full the stack is to determine if
  *      resize is necessary
  * Params:
  *      NULL
  * 
  * Returns:
  *      double ratio
  */

  double FindRatio(){
    double ratio = ((double) top + 1) / (double) size;
    return ratio;
  }

  // Getters and Setter for threshold values
  double getTooFullThresh(){
    return tooFullThresh;
  }

  void setTooFullThresh(double x){
    tooFullThresh = x;
  }

  double getTooEmptyThresh(){
    return tooEmptyThresh;
  }

  void setTooEmptyThresh(double x){
    tooEmptyThresh = x;
  }
  double getEnlargeThresh(){
    return enlargeThresh;
  }

  void setEnlargeThresh(double x){
    enlargeThresh = x;
  }
  double getShrinkThresh(){
    return shrinkThresh;
  }

  void setShrinkThresh(double x){
    shrinkThresh = x;
  }

};



// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char **argv) {

  int totalCommands;
  int r;                   // numbers being read in stored in r
  string filename;
  ArrayStack stack;       // object created
  
  ifstream myfile;        // init. myfile
  
  stack = ArrayStack();    // default case

  if(argc == 6){           /* if correct params are passed, will run with 
                            custom values and file name*/
    filename = argv[1];
    stack.setTooFullThresh(stod(argv[2]));
    stack.setTooEmptyThresh(stod(argv[3]));
    stack.setEnlargeThresh(stod(argv[4]));
    stack.setShrinkThresh(stod(argv[5]));
  }
  else{
    filename="nums.dat";
  }

  myfile.open(filename);  // reading in values from file
  while(!myfile.eof()){
    myfile >> r;
    if (r % 2 == 0){      // if else divides values by odds and evens
      stack.Push(r);
    }
    else{
      stack.Pop();
    }
  }
  
  stack.Print();          // print function call

  myfile.close();         //closing file
  return 0;
}
