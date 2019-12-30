#include <iostream>
#include "trie.h"

using namespace std;

int main()
{
    Trie vocabulary;
    cout << "Type '0'--quit;   '1'--add a word;   '2'--search a word;   '3'--search prefix: ";
    int choice;
    cin >> choice;
    while(choice) {
        if(choice == 1) {
            cout << "Add to the vocabulary this word: ";
            string word;
            cin >> word;
            vocabulary.add(word);
        } else if(choice == 2) {
            cout << "Search this word: ";
            string key;
            cin >> key;
            if(vocabulary.contains(key))
                cout << key << " exists!" << endl;
            else
                cout << key << " does not exists." << endl;
        } else if(choice == 3) {
            cout << "Search this prefix: ";
            string key;
            cin >> key;
            if(vocabulary.isPrefix(key))
                cout << key << " is a prefix." << endl;
            else
                cout << key << " is not a prefix." << endl;
        } else {
            cout << "Input incorrect. Try again." << endl;
        }
        cout << "Type '0'--quit;   '1'--add a word;   '2'--search a word;   '3'--search prefix: ";
        cin >> choice;
    }
    return 0;
}