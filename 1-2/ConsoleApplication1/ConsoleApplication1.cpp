#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>


using namespace std;


// 1-2
int permutationCheck(string a, string b) {
	if (a.length() != b.length()) {
		return 1;
	}

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	return a.compare(b);
}


// 1-3
// Counts the spaces present in a string
int countSpaces(const string & x, int start, int end, char target) {
	int count = 0;
	for (int i = start; i < end; ++i) {
		if (x[i] == target) {
			count++;
		}
	}
	return count;
}

// Replaces and ' ' with "%20"
string charReplacer(string& x, int trueLength) {
	int numSpaces = countSpaces(x, 0, trueLength, ' ');
	int newIndex = trueLength - 1 + numSpaces * 2;
	
	for (int oldIndex = trueLength - 1; oldIndex >= 0; --oldIndex) {
		if (x[oldIndex] == ' ') {
			x[newIndex] = '0';
			x[newIndex - 1] = '2';
			x[newIndex - 2] = '%';
			newIndex -= 3;
		}
		else {
			x[newIndex] = x[oldIndex];
			--newIndex;
		}
	}
	return x;
}


// 1-5

// Checks if two strings are one character away from eachother
bool oneCharEdit(const string& one, const string& two) {
	bool foundDifference = false;
	for (int i = 0; i < one.length(); ++i) {
		if (one[i] != two[i]) {
			if (foundDifference) {
				cout << one << " is NOT one character away from " << two << endl;
				return false;
			}
			foundDifference = true;
		}
	}
	cout << one << " is one character away from " << two << endl;
	return true;
}

bool oneEditInsert(const string& one, const string& two) {
	bool foundDifference = false;
	int indexOne = 0;
	int indexTwo = 0;

	while (indexTwo < two.length() && indexOne < one.length()) {
		if (one[indexOne] != two[indexTwo]) {
			if (indexOne != indexTwo) {
				cout << one << " is NOT one edit away from " << two << endl;
				return false;
			}
			indexTwo++;
		}
		else {
			indexOne++;
			indexTwo++;
		}
	}
	cout << one << " is one edit away from " << two << endl;
	return true;
}


bool oneOff(const string& one, const string& two) {
	if (one.length() == two.length()) {
		return oneCharEdit(one, two);
	}
	else if (one.length() + 1 == two.length()) {
		return oneEditInsert(one, two);
	}
	else if (one.length() - 1 == two.length()) {
		return oneEditInsert(two, one);
	}
	return false;
}



int main() {
	oneOff("peep", "beep");
	oneOff("peep", "peeld");
	oneOff("peep", "pep");
}