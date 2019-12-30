#include <iostream>
#include "trie.h"

using namespace std;

int main()
{
    Trie vocabulary;
    cout << "Type a word ('q' for quit): ";
    string word;
    cin >> word;
    while(word != "q") {
        cout << "The longest prefix is: " << vocabulary.longestPrefix(word) << endl; 
        cout << "Type a word ('q' for quit): ";
        vocabulary.add(word); //after making a search the word is added to the trie
        cin >> word;
    }
    return 0;
}

