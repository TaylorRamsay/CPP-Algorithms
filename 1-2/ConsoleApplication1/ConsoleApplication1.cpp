#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm>


using namespace std;


/* ****** TODO:
			- Add separators/descriptions for each algorithm
			- Create readme that updates when new algorithms are added

   ******			*/

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


// 1-8 Zero Matrix
	// Write an algorithm such that if an element in an M x N matrix is 0, it's entire row and column are set to 0

void nullifyRow(int matrix[4][5], int row) {
	for (int j = row; j < 5; j++) {
		matrix[row][j] = 0;
	}
}

void nullifyColumn(int matrix[4][5], int column) {
	for (int i = column; i < 4; i++) {
		matrix[i][column] = 0;
	}
}

void printMatrix(int matrix[4][5]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			cout << matrix[i][j];
		}
		cout << endl;
	}
	cout << "\n\n";
}

void zeroMatrix(int matrix[4][5]) {
	bool rowHasZero = false;
	bool columnHasZero = false;

	for (int j = 0; j < 5; j++) {
		if (matrix[0][j] == 0)
		{
			rowHasZero = true;
			break;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (matrix[i][0] == 0) {
			columnHasZero = true;
			break;
		}
	}

	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 5; j++) {
			if (matrix[i][j] == 0) {
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}

	for (int i = 1; i < 4; i++) {
		if (matrix[i][0] == 0) {
			nullifyRow(matrix, i);
		}
	}

	for (int j = 1; j < 5; j++) {
		if (matrix[0][j] == 0) {
			nullifyColumn(matrix, j);
		}
	}


	if (rowHasZero) {
		nullifyRow(matrix, 0);
	}
	
	if (columnHasZero) {
		nullifyColumn(matrix, 0);
	}

	printMatrix(matrix);
}


// ******** Linked List Algorithms ********

class Node {
public:
	int data;
	Node* prev = nullptr;
	Node* next = nullptr;
};

void insertFront(Node* &head, int data) {
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = head;
	if (head != nullptr) {
		head->prev = newNode;
	}
	head = newNode;
}

void insertBack(Node* &head, int data) {
	Node* temp = head;
	Node* newNode = new Node;
	newNode->data = data;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->prev = temp;
}

void print(Node* head) {
	while (head) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << "\n";
}


// 2.1 Remove Duplicates: Remove duplicates from an unsorted linked list

void removeDuplicate(Node* & head) {
	// start inserting elements into unordered_map
	unordered_map<int, int> node_table;
	Node* prev = head;
	Node* curr = head->next;
	node_table[head->data] = 1;
	// while curr has not reached the end of the list
	while (curr != nullptr) {
		while (curr && node_table.find(curr->data) != node_table.end()) {
			curr = curr->next;
		}
		prev->next = curr;
		prev = curr;
		if (curr) {
			node_table[curr->data] = 1;
			curr = curr->next;
		}
	}
}



// 2.2/3 Remove kth element from singly-linked list

void removeKthElement(Node* & head, int k) {
	Node* prev = head;
	Node* curr = head->next;
	if (k == 1) {
		head = curr;
	}

	for (int i = 2; i < k; i++) {
		prev = prev->next;
		curr = curr->next;
	}
	prev->next = curr->next;
}


// 2.4 Partition a linked list around a value x

Node* partition(Node* node, int x) {
	Node* head = node;
	Node* tail = node;


	while (node != nullptr) {
		Node* next = node->next;
		if (node->data < x) {
			node->next = head;
			head = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
		node = next;
	}
	tail->next = nullptr;

	return head;
}


// 2.5 Sum Lists: Two numbers are represented as a linked list in reverse order, Write a function that adds the 
//					two numbers and returns the sum as a linked list. Return the results in reverse order

int extractNum(Node* numNode) {
	int sum = 0;
	int mult = 1;
	while (numNode) {
		sum += numNode->data * mult;
		mult *= 10;
		numNode = numNode->next;
	}
	return sum;
}

void intToList(Node* list, int num) {

	list->data = num % 10;

	while (num / 10 != 0) {
		num /= 10;
		insertBack(list, (num % 10));
	}
}

Node* sumLists(Node* numOne, Node* numTwo) {
	Node* sum = new Node;

	int x = extractNum(numOne);
	int y = extractNum(numTwo);

	int z = x + y;

	intToList(sum, z);

	return sum;
}


// 2.6 Check if a list is a palindrome
Node* reverseList(Node* head) {
	Node* reverse = nullptr;
	while (head != nullptr) {
		insertFront(reverse, head->data);
		head = head->next;
	}
	return reverse;
}

bool isPalindrome(Node* head) {
	Node* reverse = reverseList(head);
	
	while (head) {
		if (head->data != reverse->data) {
			return false;
		}
		head = head->next;
		reverse = reverse->next;
	}


	return true;
}

int main() {

	/*int matrix[4][5] = {{1, 2, 3, 4, 5},
						 {6, 0, 8, 0, 1},
						 {0, 3, 4, 5, 6},
						 {7, 8, 9, 1, 2}};

	printMatrix(matrix);
	zeroMatrix(matrix);
	*/

	Node* numOne = nullptr;
	Node* numTwo = nullptr;

	srand(time(NULL));
	for (int i = 0; i < 3; i++) {
		insertFront(numOne, rand() % 5 + 1);
		insertFront(numTwo, rand() % 5 + 1);
	}

	print(numOne);
	cout << isPalindrome(numOne);
	

}