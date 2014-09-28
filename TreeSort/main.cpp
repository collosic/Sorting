#include <iostream>
#include "treesort.h"
using namespace std;

int main() {
	int C[] = {5, 8, 14, 2, 6, 11, 6, 9};
	int arrSize = sizeof(C) / sizeof(*C);
	BinarySearchTree treeSort;
	treeSort.insertEntry(5);
	cout << treeSort.getRootEntry() << endl;
	treeSort.insertEntry(8);
	treeSort.insertEntry(6);	
	return 0;
}

