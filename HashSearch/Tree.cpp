#include <string>
#include "Tree.h"
using namespace std;

Tree::Tree() {
	this->left = NULL;
	this->right = NULL;
	this->height = 1; //a leaf starts with the height of 1
}

//returns a pointer to the newly made leaf
Tree* Tree::newNode(string value) {
	Tree* node = new Tree();
	node->value = value;
	return node;
}

//returns the height of the node
int Tree::getHeight(Tree* node) {
	if (node == NULL) {
		return -1;
	}
	return node->height;
}

//returns the bigger number
int Tree::max(int x, int y) {
	if (x > y) {
		return x;
	}
	else {
		return y;
	}
}

Tree* Tree::rightRotate(Tree* b) {
	//passed in node's left node
	Tree* a = b->left;
	//a's right node
	Tree* temp = a->right;

	//b is now a's right node
	a->right = b;
	//b's left node is now a's right node
	b->left = temp;

	//sets the height matching to the newly made balance
	b->height = max(getHeight(b->left), getHeight(b->right)) + 1;
	a->height = max(getHeight(a->left), getHeight(a->right)) + 1;

	//return the new (sub)Tree's root node
	return a;
}

Tree* Tree::leftRotate(Tree* a) {
	//passed in node's right node
	Tree* b = a->right;
	//b's left node
	Tree* temp = b->left;

	//a is now b's left node
	b->left = a;
	//a's right node is now b's left node
	a->right = temp;

	//sets the height matching to the newly made balance
	a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
	b->height = max(getHeight(b->left), getHeight(b->right)) + 1;

	//return the new (sub)Tree's root node
	return b;
}

//returns the balance between node's left and right
int Tree::balance(Tree* node) {
	if (node == NULL) {
		return 0;
	}
	return getHeight(node->left) - getHeight(node->right);
}

//recursive function that goes to the end of the Tree and inserts the value
//and balances while it tracks back up by returning each height's node
//and checking the balance
Tree* Tree::doInsert(Tree* node, string value) {
	if (node == NULL) {
		return newNode(value);
	}
	if (value == node->value) {
		return node;
	}
	if (value < node->value) {
		/*RECURSION until it reaches the end*/
		//left node gets the root of the previous (sub)Tree
		node->left = doInsert(node->left, value);
	}
	else {
		/*RECURSION until it reaches the end*/
		//right node gets the root of the previous (sub)Tree
		node->right = doInsert(node->right, value);
	}

	//new height after inserting
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;


	//Left-Left
	if (balance(node) > 1 && value < node->left->value) {
		return rightRotate(node);
	}
	//Left-Right
	if (balance(node) > 1 && value > node->left->value) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	//Right-Right
	if (balance(node) < -1 && value > node->right->value) {
		return leftRotate(node);
	}
	//Right-Left
	if (balance(node) < -1 && value < node->right->value) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	//a new root for the (sub)Tree should have been returned at this point

	//Return if the balance was fine for this node
	return node;
}

//search for a certain value and return either true or false
bool Tree::search(Tree* node, string value) {
	if (node == NULL) {
		return false;
	}
	if (value == node->value) {
		return true;
	}
	if (value < node->value) {
		return search(node->left, value);
	}
	else {
		return search(node->right, value);
	}
}