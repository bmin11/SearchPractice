#include <string>
#include <vector>
#include "Hash.h"

//Constructor with a list length of 11 holding a list
Hash::Hash() {
	list = vector<vector<string>>(47, vector<string>());
}

//Gets the hash value of the string
int Hash::hashValue(string value) {
	int sum, index;

	sum = 0;
	int len = value.length();
	for (int i = 0; i < len; i++) {
		sum += (int)value[i];
	}

	index = sum % 47; //Primary number that matches the array size. Would be better to have it longer than this.

	return index;
}

//adds the value only when the value itself doesn't exist
void Hash::add(string value) {
	if (!contains(value)) {
		int index = hashValue(value);
		//adds the value to the back of the list of chosen index
		list[index].push_back(value);
	}
}

//finds if the list has the value
bool Hash::contains(string value) {
	int index = hashValue(value);

	return find(list[index].begin(), list[index].end(), value) != list[index].end();
}