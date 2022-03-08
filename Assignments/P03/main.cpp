///////////////////////////////////////////////////////////////////
//
// Author:           Aodhan Shaw
// Email:            aodhanshaw@gmail.com
// Label:            Program 3
// Title:            Program 03 - Processing in trie tree time
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//  Using a trie tree to store all words from the dictionary, 
//  we implement an autosuggestion feature and calculate
//  the time it takes to search through trie tree.
//
//
///////////////////////////////////////////////////////////////////

// Included libraries
#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Define the character size
#define CHAR_SIZE 26

// Checks if uppercase
bool isUpper(char letter) {
    int l = letter;
    return (l >= 65 && l <= 90);
}

// Checks if lowercase
bool isLower(char letter) {
    int l = letter;
    return (l >= 97 && l <= 122);
}

// Checks if letter
bool isLetter(char letter) {
    int l = letter;
    return isUpper(l) || isLower(l);
}

bool isAlphaOnly(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (!isLetter(word[i])) {
            return false;
        }
    }
    return true;
}

void makeUpper(string &word) {
    for (int i = 0; i < word.length(); i++) {
        if (isLower(word[i])) {
            word[i] -= 32;
        }
    }
}

////////////////////////////////////////
// struct TrieNode
// 
// Description:
//  node that holds a character
//  
// 
// Public Methods:
//      - TrieNode()
// 
// Usage: 
//      - See main program
//      
////////////////////////////////////////
struct TrieNode {
    bool isLeaf;
    TrieNode *character[CHAR_SIZE];
    TrieNode() {
        this->isLeaf = false;

        for (int i = 0; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }
    }
};

vector<char> countLetters(string filename) {
    ifstream fin;
    vector<char> alph;

    fin.open(filename);

    string word;
    while (!fin.eof()) {
        fin >> word;
        for (int j = 0; j < word.size(); j++) {
            if (std::find(alph.begin(), alph.end(), word[j]) == alph.end()) {
                alph.push_back(word[j]);
            }
        }
    }
    return alph;
}

/////////////////////////////////////////////////////
// Class Trie
// 
// Description:
//      Trie that hold TrieNode
// Private Variables:
//      TrieNode *root;
//    bool deletion(TrieNode *&, string);
//    void find_all(TrieNode *&, string);
//    vector<string> results;
// Public Variables:
//      
// Public Methods:
//      - Trie()
//      - insert(string)
//      - deletion(string)
//      - search(string)
//      - haveChildren(TrieNode const *)
//      - vector<string> find_all(string)
// Usage: 
//      - See main program
//      
/////////////////////////////////////////////////////
class Trie {
    TrieNode *root;
    bool deletion(TrieNode *&, string);
    void find_all(TrieNode *&, string);
    vector<string> results;

public:
    Trie() {
        root = new TrieNode;
    }
    void insert(string);
    bool deletion(string);
    bool search(string);
    bool haveChildren(TrieNode const *);
    vector<string> find_all(string);
};


void Trie::find_all(TrieNode *&curr,string key){

    if(curr->isLeaf){
        results.push_back(key);
    }

    for (int i = 0; i < 26; i++) {
        if(curr->character[i]){
            find_all(curr->character[i],key+char(i+65));
        }
    }
}

vector<string> Trie::find_all(string key){
    makeUpper(key);
    TrieNode* curr = root;
    bool isValidKey = false;
    results.clear();

    for (int i = 0; i < key.length(); i++) {
        // go to the next node

        if(!isLetter(key[i])) // If the char is not a letter, end loop
        {
          isValidKey = false;
          i = key.length();  // stop the loop
        }
        else if(curr->character[key[i] - 65] == nullptr) // If element is nullptr, end loop
        {
          isValidKey = false;
          i = key.length();
        }
        else
        {
          curr = curr->character[key[i] - 65];
          isValidKey = true;
        }
    }

    if(isValidKey) // Finds all partial matches if the path exists in the trie
    find_all(curr,key);
  cout << termcolor::red << results.size() << termcolor::reset;
    return results;
}

// Iterative function to insert a key into a Trie
void Trie::insert(string key) {
    makeUpper(key);

    //cout<<key<<endl;

    // start from the root node
    TrieNode *curr = root;
    for (int i = 0; i < key.length(); i++) {

        // create a new node if the path doesn't exist
        if (curr->character[key[i] - 65] == nullptr) {
            curr->character[key[i] - 65] = new TrieNode();
        }

        // go to the next node
        curr = curr->character[key[i] - 65];
    }

    // mark the current node as a leaf
    curr->isLeaf = true;
}

// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie; otherwise, it returns false
bool Trie::search(string key) {
    makeUpper(key);
    TrieNode *curr = root;
    // return false if Trie is empty
    if (curr == nullptr) {
        return false;
    }

    for (int i = 0; i < key.length(); i++) {

        // go to the next node
        curr = curr->character[key[i] - 65];

        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return false;
        }
    }

    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

// Returns true if a given node has any children
bool Trie::haveChildren(TrieNode const *curr) {
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (curr->character[i]) {
            return true; // child found
        }
    }

    return false;
}


bool Trie::deletion(string key) {
    makeUpper(key);
    return deletion(root, key);
}

// Recursive function to delete a key in the Trie
bool Trie::deletion(TrieNode *&curr, string key) {

    // return if Trie is empty
    if (curr == nullptr) {
        return false;
    }

    // if the end of the key is not reached
    if (key.length()) {
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)

        if (curr != nullptr &&
            curr->character[key[0] - 65] != nullptr &&
            deletion(curr->character[key[0] - 65], key.substr(1)) && curr->isLeaf == false) {
            if (!haveChildren(curr)) {
                delete curr;
                curr = nullptr;
                return true;
            } else {
                return false;
            }
        }
    }

    // if the end of the key is reached
    if (key.length() == 0 && curr->isLeaf) {
        // if the current node is a leaf node and doesn't have any children
        if (!haveChildren(curr)) {
            // delete the current node
            delete curr;
            curr = nullptr;

            // delete the non-leaf parent nodes
            return true;
        }

        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;

            // don't delete its parent nodes
            return false;
        }
    }

    return false;
}

void loadWords(Trie *&T) {
  ifstream fin;      // infile
  size_t found;     
  string word;
  int count = 0;
  fin.open("dictionary.txt");

  while (!fin.eof()) // while loop that passes each word to insert function
  {
    fin >> word;
    if (isAlphaOnly(word)) {
      T->insert(word);
      count++;
    }
  }
  cout << termcolor::magenta << "Words Loaded!\n" << termcolor::reset;
  cout << "Total Words = " << count << endl;
  fin.close();
}

// C++ implementation of Trie data structure
int main() {
  Trie *T = new Trie();     // creating instance of Trie
  Timer timer;              // init. timer
  vector<string> results;   // vector for auto suggestions
  string word = "";
  char k;

  cout << "loading dictionary..." << endl;
  timer.Start();            // starting timer
  loadWords(T);
  timer.End();              // timer end
  cout << termcolor::red;
  cout << timer.MilliSeconds() << termcolor::reset
       << " milliseconds to read in and load words into trie\n\n";

  cout << "------------------------------------------------------------\n";
  cout << termcolor::cyan
       << "TYPE IN LOWERCASE KEYS TO SEARCH. TYPE CAPITAL 'Z' TO QUIT."
       << termcolor::reset << endl;
  cout << "------------------------------------------------------------\n\n";

  while ((k = getch()) != 'Z') {
    timer.Start(); // start timer
    // Tests for a backspace and if pressed deletes
    // last letter from "word".
    if ((int)k == 127) {
      if (word.size() > 0) {
        word = word.substr(0, word.size() - 1);
      }
    } else {
      // Make sure a letter was pressed and only letter
      if (!isalpha(k)) {
        cout << "Letters only!" << endl;
        continue;
      }

      // We know its a letter, lets make sure its lowercase.
      // Any letter with ascii value < 97 is capital so we
      // lower it.
      if ((int)k < 97) {
        k += 32;
      }
      word += k; // append char to word
    }

    results = T->find_all(word);  // function call to load vector with auto sugg.

    if ((int)k != 32) { // if k is not a space print it
      timer.End();
      cout << " words found in " << termcolor::red << timer.MilliSeconds()
           << termcolor::reset << " Milliseconds" << endl;
      cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k
           << termcolor::reset << endl;
      cout << "Current Substring: " << termcolor::bright_yellow << word
           << termcolor::reset << endl;
      cout << "Words Found: ";
      cout << termcolor::green;
      // This prints out all found matches
      for (int i = 0; i < 10; i++) {
        cout << results[i] << ", ";
      }
      cout << termcolor::reset << endl << endl;
    }
  }
  
  return 0;
}
