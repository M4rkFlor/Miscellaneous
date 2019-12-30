#ifndef TRIE_H
#define TRIE_H

#define MAX_CHAR 256 //should be 128 since that is standard char/ASCII table range
using namespace std;

class Node
{
private:
    Node *children[MAX_CHAR];//each node in trie can have a maximum of 256 children
    bool bisEnd;//flag
public:
    Node();
    bool isEnd();//check flag
    void insert(string suffix); //insert item to trie
    Node* search(string pat);//search trie
};

class Trie
{
private:
    Node root;
public:
    void add(string word);// adds word to trie
    bool contains(string pat); //check if a a word is in the trie that has been terminiated
    bool isPrefix(string pat); //checks if prefix is in trie
    string longestPrefix(string);// longest common prefix
};
#endif