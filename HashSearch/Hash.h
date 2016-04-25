#ifndef HASH
#define HASH
#include <string>
#include <vector>
using namespace std;

class Hash {
public:
	vector<vector<string>> list;
	Hash();
	int hashValue(string);
	void add(string);
	bool contains(string);
};
#endif