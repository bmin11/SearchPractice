#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Tree.h"
#include "Hash.h"
using namespace std;

bool sequentialSearch(const int*, const int&, const int&);
bool binarySearch(const int*, const int&, int, int);
void printTree(Tree*, int);
void printHash(Hash*);
vector<string> split(string);
bool notAlphabet(char);
string lowercase(string);

int main() {
	int list[30000];
	int l = 30000;
	for (int i = 0; i < l; i++) {
		list[i] = i + 1;
	}

	int counter = 0;
	cout << "Sequential searching...." << endl;
	clock_t start = clock();
	for (int x = 0; x < l; x++) {
		if (sequentialSearch(list, l, x + 1)) {
			counter++;
		}
	}
	double duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Found " << counter << " records" << endl;
	cout << "Done! Took " << duration << " seconds." << endl;

	counter = 0;
	cout << "Binary searching...." << endl;
	start = clock();
	for (int x = 0; x < l; x++) {
		if (binarySearch(list, x + 1, 0, l)) {
			counter++;
		}
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Found " << counter << " records" << endl;
	cout << "Done! Took " << duration << " seconds." << endl;
	cout << endl << "Press enter to make both Tree and Hash";
	_getch();
	cout << endl;


	Tree* root = NULL;

	/*
	for (int i = 0; i < 100; i++) {
	root = root->doInsert(root, i);
	}

	printTree(root, 0);
	*/

	string line;
	//insert all words in dictionary.txt into the Tree
	//Tree balances it itself while inserting
	//a new root node must be maintained after an insert
	ifstream file("dictionary.txt");
	start = clock();
	if (file.is_open()) {
		while (getline(file, line)) {
			root = root->doInsert(root, line);
		}
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	printTree(root, 0);
	cout << "Done. Took " << duration << " seconds." << endl;

	cout << endl;

	Hash hash = Hash();
	file = ifstream("dictionary.txt");
	start = clock();
	if (file.is_open()) {
		while (getline(file, line)) {
			hash.add(line);
		}
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	printHash(&hash);
	cout << endl << "Done. Took " << duration << " seconds." << endl << endl;

	cout << "Press enter to start searching on Tree and Hash";
	_getch();

	cout << endl << endl;
	vector<string> tokens;
	//splits and cuts the string into multiple search friendly string
	file = ifstream("mispelled.txt");
	if (file.is_open()) {
		getline(file, line);
		line.erase(remove_if(line.begin(), line.end(), notAlphabet), line.end());
		tokens = split(line);
	}
	cout << endl << endl << "TREE SEARCH" << endl;

	clock_t searchTime = clock();
	for (int i = 0; i < tokens.size(); i++) {
		//search the string in lowercase
		//print whatever string that was not found in the Tree
		start = clock();
		if (!root->search(root, lowercase(tokens.at(i)))) {
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "After " << duration << " seconds... Could not find:\t" + tokens.at(i) << endl;
		}
	}
	duration = (clock() - searchTime) / (double)CLOCKS_PER_SEC;
	cout << "Search done. Took " << duration << " seconds.";

	cout << endl << endl << "HASH SEARCH" << endl;

	searchTime = clock();
	for (int i = 0; i < tokens.size(); i++) {
		//search the string in lowercase
		//print whatever string that was not found in the Hash
		start = clock();
		if (!hash.contains(lowercase(tokens.at(i)))) {
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "After " << duration << " seconds... Could not find:\t" + tokens.at(i) << endl;
		}
	}
	duration = (clock() - searchTime) / (double)CLOCKS_PER_SEC;
	cout << "Search done. Took " << duration << " seconds.";

	_getch();
	return 0;
}

bool sequentialSearch(const int* list, const int &length, const int &target) {
	for (int i = 0; i < length; i++) {
		if (list[i] == target) {
			return true;
		}
	}
	return false;
}

bool binarySearch(const int* list, const int &target, int bottom, int top) {
	int mid = (bottom + top) / 2;
	while (list[mid] != target) {
		if (list[mid] < target) {
			bottom = mid + 1;
			mid = (bottom + top) / 2;
		}
		else if (list[mid] > target) {
			top = mid;
			mid = (bottom + top) / 2;
		}
	}
	return list[mid] == target;
}

void printTree(Tree* root, int indent)
{
	if (root != NULL) {
		if (indent) {
			for (int i = 0; i < indent / 8; i++) {
				std::cout << std::setw(8) << ' ';
				cout << "|";
			}
		}
		cout << root->value << "\n ";
		if (root->left) {
			cout << "|";
			printTree(root->left, indent + 8);
		}
		if (root->right) {
			cout << "|";
			printTree(root->right, indent + 8);
		}
	}
}

void printHash(Hash* hash)
{
	for (int i = 0; i < hash->list.size(); i++) {
		for (int j = 0; j < hash->list[i].size(); j++) {
			cout << hash->list[i][j] << " ";
		}
		cout << endl;
	}
}

vector<string> split(string line) {
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;

	vector<string> tokens(beg, end);

	return tokens;
}

bool notAlphabet(char c) {
	c = tolower(c);
	return ((c < 'a' || c > 'z') && c != ' ');
}

string lowercase(string line) {
	for (int i = 0; i < line.length(); i++) {
		line[i] = tolower(line[i]);
	}
	return line;
}