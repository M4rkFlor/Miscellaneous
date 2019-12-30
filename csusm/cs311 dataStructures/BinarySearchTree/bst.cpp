#include <iostream>
#include "bst.h"

using namespace std;

BST::BST() 
{
    //constructor
    root = nullptr;
}
BST::~BST() 
{
    //Performs deep delete recursively
    DeepDelete(root);
}

void BST::DeepDelete(Node* node)
{
    if (node!=nullptr)
    {
        DeepDelete(node->left);//find left most node
        DeepDelete(node->right);//Then delete right nodes
        delete node;
    }
}

void BST::insert(int data) {
	//////////////////
    root = insert(root,data);
}  
Node* BST::insert(Node* node, int data) {
    //////////////////
    if(node == nullptr){
        node = new Node(data);//If the tree is NULL, we add the new Node as the root node.
	} else if(node->key > data) {
        node->left = insert(node->left, data);// if the key is less than that of the root, we add the new Node to the left subtree.
    } else if(data > node->key) {
        node->right = insert(node->right, data);//If the key is greater than that of the root, we add the new Node to the right subtree.
    }
	return node;
}

Node* BST::search(int key) {
	//////////////////
    return search(root, key);//returns null if not found
}
Node* BST::search(Node* node, int key) {
    //////////////////
    if (node == NULL || node->key == key)
        return node;//returns null if key dosent exist otherwise will return self
    if (node->key < key)
        return search(node->right, key);//search right if key is greater
	return search(node->left, key);//otherwise search left
}

void BST::inorder() {
    //prints in order
    inorder(root);
}
void BST::inorder(Node* node) {
    //print in order
    if (node != nullptr)
    {
        inorder(node->left);//Traverse to left most node
        cout  <<  node->key  <<  " ";//then print
        inorder(node->right);//then traverse and print their right nodes
    }
}
		
void BST::remove(int key)
{
	//////////////////
    remove(root, key);
}
Node* BST::remove(Node* node, int key)
{
    //////////////////
    if (node == nullptr)
		return node;
	if (node->key > key)
		node->left = remove(node->left, key);
 	else if (key > node->key)
        node->right = remove(node->right, key);
	else//at this point, Key == node->key
	{
        // Case 1 & 2: node with only one child or no child
        if (node->left == nullptr)
        {
            Node *temp = node->right;
            delete node;
            return temp;//return the newNode placed in the position of the deleted node
        }
        // Case 1 & 2: node with only one child or no child
        else if (node->right == nullptr)
        {
            Node *temp = node->left;
            delete node;
            return temp;
        }
        // Case 3: node with two children: Get the leftmost node from the left subtree)
        Node* temp = leftmostNode(node->left);
        node->key = temp->key;
        node->left = remove(node->left, temp->key);
    }
    return node;
}

Node* BST::leftmostNode(Node* node)
{
	//////////////////
    Node* current = node;
    	/* loop down to find the leftmost leaf */
    	while (current->right != nullptr)
            current = current->right;
		return current;
}
