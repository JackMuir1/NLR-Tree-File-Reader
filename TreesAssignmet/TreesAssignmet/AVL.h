#pragma once
#include "Node.h"

class AVL
{
public:

	//Function to Read and print tree from c:\\temp\\input.txt
	void getfile();

	//Default Constructor
	AVL();

	//Creates a new Node - performs similarly to constructor with pointer
	Node* newNode(int key);

	//Recursively inserts a node into the correct leaf of the tree, returns root - balances as well
	Node* insert(Node* node, int key);

	//Recursively deletes a node into the correct leaf of the tree, returns root - balances as well
	Node* deleteNode(Node* root, int key);

	//Prints the tree in preorder (NLR)
	void preOrder(Node *root);

};