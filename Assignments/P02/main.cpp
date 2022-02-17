///////////////////////////////////////////////////////////////////
//
// Author:           Aodhan Shaw
// Email:            aodhanshaw@gmail.com
// Label:            Program 2
// Title:            Program 02 - Processing in Linear time
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//  Using a linked list to store all words from the dictionary, 
//  we implement an autosuggestion feature and calculate
// the time it takes to search through linked list.
//
//
///////////////////////////////////////////////////////////////////

// Libraries
#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define RED termcolor::red

/**
 * struct wordNode
 * 
 * Description:
 *  node that holds a string word
 *  and a pointer to next pointer
 * 
 * Public Methods:
 *      - N/A
 * 
 * Usage: 
 *      - See main program
 *      
 */

struct wordNode{
  string word;
  string definition;
  wordNode *next;
};

/**
 * Class linkedList
 * 
 * Description:
 *      linked list that hold wordNodes
 * Private Method:
 *      - wordNode *head, *tail
 *
 * Public Methods:
 *      - linkedList()
 *      - display()
 *      - loadWords()
 *      - addNode(string line)
 *      - findMatches()
 * 
 * Usage: 
 *      - See main program
 *      
 */

class linkedList{
  private:
  wordNode *head, *tail;
  public:
  linkedList(){
    head = NULL;
    tail = NULL;
  }

  void display(){
    wordNode *tmp;
        tmp = head;
        while (tmp != NULL)
        {
            cout << tmp->word << endl;
            tmp = tmp->next;
        }
    }

  void loadWords(){
    ifstream fin;
    string line;
    fin.open("dictionary.txt");

    while(getline(fin,line))
    {
      addNode(line);
    }
    cout << termcolor::magenta << "Words Loaded!\n"<< termcolor::reset;
  }  

  void addNode(string line){
    wordNode *tmp = new wordNode;
    tmp->word = line;
    tmp->next = NULL;

    if(head == NULL)
    {
      head = tmp;
      tail = tmp;
    }
    else
    {
      tail->next = tmp;
      tail = tail->next;
    }
  }

vector<string> findMatches(linkedList &LL, string substring){

  vector<string> matches;
  size_t found;
  wordNode *tmp;
  tmp = head;
        while (tmp != NULL)
        {
          found = tmp->word.find(substring);
          matches.push_back(tmp->word);
          if(found != string::npos){
            matches.push_back(tmp->word);
          }
          tmp = tmp->next;
        }

  return matches;
  }

};


int main() {
linkedList LL;          // instance of linked linkedList
vector<string> matches; // vector to hold matches
string word = "";
char k;
int loc;

Timer T;                // initialize timer
T.Start();

LL.loadWords();         // function call to load linked list 
T.End();

cout << termcolor::red;
cout << T.MilliSeconds() << termcolor::reset << " milliseconds to read in and load words into linked list\n\n";

cout << termcolor::cyan << "TYPE IN LOWERCASE KEYS TO SEARCH. TYPE CAPITAL 'Z' TO QUIT." << termcolor::reset << endl;

while ((k = getch()) != 'Z') {
  T.Start();  // start it
  // Tests for a backspace and if pressed deletes
  // last letter from "word".
  if ((int)k == 127){
    if (word.size() > 0){
    word = word.substr(0, word.size() - 1);
    }
  } 
  else{
  // Make sure a letter was pressed and only letter
    if (!isalpha(k)){
    cout << "Letters only!" << endl;
    continue;
    }

  // We know its a letter, lets make sure its lowercase.
  // Any letter with ascii value < 97 is capital so we
  // lower it.
    if ((int)k < 97){
      k += 32;
    }
    word += k; // append char to word
  }


matches = LL.findMatches(LL, word);

          if ((int)k != 32) { // if k is not a space print it
            T.End();
            cout << T.NanoSeconds() << " nano" << endl;
            cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << "Words Found: ";
            cout << termcolor::green;
            // This prints out all found matches
            for (int i = 0; i < word.size(); i++) {
                // find the substring in the word
                loc = matches[i].find(word);
                // if its found
                if (loc != string::npos) {
                    //print one letter at a time turning on red or green
                    // depending on if the matching subtring is being printed
                    for (int j = 0; j < matches[i].size(); j++) {
                        // if we are printing the substring turn it red
                        if (j >= loc && j <= loc + word.size() - 1) {
                            cout << termcolor::red;
                        } else {
                            cout << termcolor::green;
                        }
                        cout << matches[i][j];
                    }
                    cout << termcolor::green;
                }
                cout << " ";
            }
            cout << termcolor::reset << endl
                 << endl;
        }
}

return 0;

}
