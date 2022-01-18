```
/*****************************************************************************
*                    
*  Author:           Aodhan Shaw
*  Email:            aodhanshaw@gmail.com
*  Label:            A04b
*  Title:            Commenting Assignment / Linked list
*  Course:           3013-Algorithms
*  Semester:         Spring Semester 2022
* 
*  Description:
* Linked list
*****************************************************************************/

#include <iostream>   // Including library

using namespace std;  

int A[100];           // initiatizing array of 100

/******************************************************************************
* Struct: Node
* 
* Description:
*      This struct represents objects of type "Node" which are implemented in
* the linked lists. Contains integer values x and standard constructor as well
* as an overloaded constuctor.
* 
* Public Methods:
*       
*      Node()
*      Node(int)
*      int x
*      
* Private Methods:
*      N/A
*       
* 
******************************************************************************/

struct Node {
    int x;
    Node *next;
    Node() {
        x = -1;
        next = NULL;
    }
    Node(int n) {
        x = n;
        next = NULL;
    }
};

/******************************************************************************
* Class: List
* 
* Description:
*      This class is used to create a linked list and performs funxtions 
* such as pushing and popping items onto list as well as printing the items.
* 
* Public Methods:
*       
*      List()
*      void Push(int val)
*      void Insert(int val)
*      void PrintTail()
*      string Print()
*      int Pop()
*      
* Private Methods:
*      Node *Head
*      Node *Tail
*      int Size
*       
* Usage:
* List L1
* List L2
* List L3 = L1 + L2;
* 
******************************************************************************/

class List {
private:
    Node *Head;   // pointer that keeps track of the head
    Node *Tail;   // pointer that keeps track of tail
    int Size;

public:
    List() {
        Head = Tail = NULL;
        Size = 0;
    }

    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

    void PrintTail() {
        cout << Tail->x << endl;
    }

    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented
    int Pop() {
        Size--;   // decrements size
        return 0; 
    }

    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    // overloading ostream
    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

/**
* Main Driver
* 
* For this program, the main driver was used to test the LInked List
* 
*/

int main(int argc, char **argv) {
    List L1;            // creating object of type list
    List L2;            // creating object of type list

    for (int i = 0; i < 25; i++) {
        L1.Push(i);     // loop to push items onto list
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);     // loop to push items onto list
    }

    //cout << L1 << endl;
    L1.PrintTail();     // function to print tail
    L2.PrintTail();

    List L3 = L1 + L2;   // overloading addition operator
    cout << L3 << endl;

    cout << L3[5] << endl; // overloading [] operator
    return 0;
}
