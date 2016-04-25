#ifndef TREE
#define TREE
#include <string>
using namespace std;

class Tree {
public:
	Tree* left;
	Tree* right;
	int height;
	string value;
	Tree();
	Tree* newNode(string);
	int getHeight(Tree*);
	int max(int, int);
	Tree* rightRotate(Tree*);
	Tree* leftRotate(Tree*);
	int balance(Tree*);
	Tree* doInsert(Tree*, string);
	bool search(Tree*, string);
};
#endif