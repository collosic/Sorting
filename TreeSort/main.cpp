#include <iostream>
#include "treesort.h"
using namespace std;

int main() {
	int C[] = {5, 8, 14, 2, 6, 11, 6, 9};
	int arrSize = sizeof(C) / sizeof(*C);
	BinarySearchTree treeSort;
	for (int i = 0; i < arrSize; i++) {
		treeSort.insertEntry(C[i]);
	}
	treeSort.displayTree(true);
	return 0;
}
