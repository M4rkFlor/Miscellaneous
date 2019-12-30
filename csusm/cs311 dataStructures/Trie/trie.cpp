#include <iostream>
#include "trie.h"

using namespace std;
/* Node helper class implementation here */
Node::Node() {//constructor
    for(int i = 0; i < MAX_CHAR; i++)
          children[i] = NULL;//set all children to null
    bisEnd = false;//set flag
}

bool Node::isEnd() {
    return bisEnd; //flag
}

void Node::insert(string s) {
    if(s.length() <= 0) //if string is empty do nothing
        return; 
    unsigned char c = s.at(0); //get first char of string also changed to unsigned char to reach the extended ASCII table range
    if (children[c] == NULL)
        children[c] = new Node();//if char is not a child then make it a child
    if(s.length() == 1)
        children[c]->bisEnd = true;//set flag that the string ended
    else
        children[c]->insert(s.substr(1));// call insert for next character in string until string ends
}

Node* Node::search(string s) {
    if (s.length() == 0)
        return this; //return the last node
    unsigned char c = s.at(0); //get first char of string also changed to unsigned char to reach the extended ASCII table range
    if (children[c] == NULL)
        return NULL; //if no more children and char is not in trie, then the string is not in the trie, so we return nothing
    return children[c]->search(s.substr(1));//search for the next charcter in string in the Trie
}

/* add your Trie implementation here */
void Trie::add(string word) {
    root.insert(word); // add word to the trie
}

bool Trie::contains(string pat) {
    Node* node = root.search(pat);//search string in trie, returns last node if string path exists
    if(node != NULL && node->isEnd())
        return true; // found a terminating path
    return false; // path not found in trie
}

bool Trie::isPrefix(string pat) { //same as conatins except it dosent need to be a terminating path.
    Node* node = root.search(pat);
    return node == NULL ? false : true;//if a string path exisists in the trie return true
}

string Trie::longestPrefix(string s){
    unsigned char len = s.length();
    if(len==0)
        return "";
    string longestPrefix;
    int max = 0;
    int i=1;
    while(i<len){//this stops one early to prevent matching self
        if(isPrefix(s.substr(0,i))){
            max=i;
        }
        i++;
    }
    return s.substr(0,max);//return the longest Prefix
}