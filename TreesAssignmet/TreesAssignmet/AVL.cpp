#include <iostream>
#include <fstream> //For file reading
#include <string>
#include "AVL.h"
#include "Node.h"

using namespace std;

//Default Constructor
AVL::AVL()
{}

//UTILITY FUNCTIONS

//Returns the height of a node, with a base case
int getHeight(Node *N)
{
	//If there is no nodes, height is 0
	if (N == NULL)
		return 0;
	return N->height;
}

//Returns the max of two integers for organizational purposes
int getMax(int a, int b)
{
	return (a > b) ? a : b;
}

// Get Balance factor of nodes to determine rotation
int getBalance(Node *N)
{
	//Base Case- No nodes would be 0
	if (N == NULL)
		return 0;
	return getHeight(N->left) - getHeight(N->right); //Creates negative if right is largers, positive for left
}

//Find the smallest node in the tree
Node * minimumNode(Node* node)
{
	Node* currentNode = node;

	//find the leftmost leaf
	while (currentNode->left != NULL)
		currentNode = currentNode->left;

	return currentNode;
}

//TREE FUNCTIONS

//Function to Read and print tree from c:\\temp\\input.txt
void AVL::getfile()
{
	ifstream infile("c:\\temp\\input.txt"); //Input file, as stated in rubrc

	string s; //String used in storing lines from file

	Node *root = NULL; //Started node for created tree

	while (infile) //Loop through entire file
	{
		//For clarity purposes, print each line of file commands
		getline(infile, s); 
		cout << s << endl;

		//Case 1: Add node with 'a'
		if (s[0] == 'a')
		{
			//Find integer in line
			int i = 0;
			string numToConvert;

			//For multiple digit integers, loop through line, adding only integers
			while (s[i] != NULL)
			{
				if (isdigit(s[i]))
				{
					numToConvert += s[i];
				}
				i++;
			}
			int x = stoi(numToConvert);

			//Add node with key of integer received
			root = insert(root, x);
		}
		//Case 2: Delete node with 'd'
		else if (s[0] == 'd')
		{

			//Find integer in line
			int i = 0;
			string numToConvert;

			//For multiple digit integers, loop through line, adding only integers
			while (s[i] != NULL)
			{
				if (isdigit(s[i]))
				{
					numToConvert += s[i];
				}
				i++;
			}
			int x = stoi(numToConvert);

			//Delete node with key of integer received
			root = deleteNode(root, x);
		}
		//Break Case: end tree with 'e'
		else if (s[0] == 'e')
			break;
	}
	
	//Print the NLR traversal of the tree
	cout << endl << "The tree in NLR format is: ";
	preOrder(root);
	cout << endl;
	//Close file
	infile.close();
}

//Prints the tree in preorder (NLR)
void AVL::preOrder(Node *root)
{
	if (root != NULL)
	{
		cout << root->key << " "; //N
		preOrder(root->left); //L
		preOrder(root->right); //R
	}
}

//NODE FUNCTIONS

//Creates a new Node - performs similarly to constructor with pointer
Node* AVL::newNode(int key)
{
	//Creates new Node with key and height 1
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // new node is placed at leaf, so it increases height of tree by 1
	return(node);
}

//Rotates a subtree right to balance the avl tree
Node *rightRotate(Node *y)
{
	//Storage variables for the rotates nodes
	Node *newRoot = y->left;
	Node *T2 = newRoot->right;

	//Swap variables to rotate
	newRoot->right = y;
	y->left = T2;

	// Update heights recursively
	y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
	newRoot->height = getMax(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

	// Return new root
	return newRoot;
}

//Rotates a subtree left to balance the avl tree
Node *leftRotate(Node *x)
{
	//Storage variables for the rotates nodes
	Node *newRoot = x->right;
	Node *T2 = newRoot->left;

	//Swap variables to rotate
	newRoot->left = x;
	x->right = T2;

	// Update heights recursively
	x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
	newRoot->height = getMax(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

	// Return new root
	return newRoot;
}

//INSERTION AND DELETION FUNCTIONS

//Recursively inserts a node into the correct leaf of the tree, returns root - balances as well
Node* AVL::insert(Node* node, int key)
{
	//Base Case- Insert a node into empty tree
	if (node == NULL)
		return(newNode(key));

	//Left Case - Smaller Nodes to the Left
	if (key < node->key)
		node->left = insert(node->left, key);

	//Right Case - Larger Nodes to the right
	else if (key > node->key)
		node->right = insert(node->right, key);
	// Equal keys are not allowed in AVL
	else 
		return node;

	//Change height of previous node
	node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));

	//Get balance of previous node to determine rotations
	int balance = getBalance(node);

	// Left Left of unbalance - rotate right
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right unbalance - rotate left
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right unbalance - rotate left right 
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left unbalance - rotate right left
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	//Return the node after rotation
	return node;
}

//Recursively deletes a node into the correct leaf of the tree, returns root - balances as well
Node* AVL::deleteNode(Node* root, int key)
{

	//Null Case- Do not delete nonexistant tree
	if (root == NULL)
		return root;

	//Left Case - Smaller Nodes to the Left
	if (key < root->key)
		root->left = deleteNode(root->left, key); //continue recursively

	//Right Case - Larger Nodes to the right 
	else if (key > root->key)
		root->right = deleteNode(root->right, key); //continue recursively

	//Once the key matches the key to delete, perform deletion based on position
	else
	{
		// node with less than 2 children 
		if ((root->left == NULL) || (root->right == NULL))
		{
			Node *temp = root->left ? root->left : root->right; //Statement to determine whether node is left or right

			//If right nor left exist, delete node without deleting root
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}

			//If one child
			else 
				*root = *temp; //Copy children that are not null

			//Deallocate node to delete
			free(temp);
		}

		//Nodes with two children
		else
		{
			//Get the smallest in the right subtree
			Node* temp = minimumNode(root->right);

			// Copy the next Node's data to this node 
			root->key = temp->key;

			// Delete the next Node 
			root->right = deleteNode(root->right, temp->key);

			//NOTE: This can create different preorder traversals than shown in the simulation
			//However, they are still perfectly balanced, as preorder traversal of AVL trees can differ
			//in each case
		}
	}

	//Single rooted tree
	if (root == NULL)
		return root;

	//update root's height for balancing
	root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));

	//Get balance of root to determine rotations
	int balance = getBalance(root);

	// Left Left of unbalance - rotate right
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right unbalance - rotate left right 
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	
	// Right Left unbalance - rotate right left 
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	// Right Right unbalance - rotate left
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	return root;
}
