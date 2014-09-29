// Example main.cpp on how to use treesort.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "treesort.h"

int main() {
    srand(time(NULL));
    int size = 20;
    BinarySearchTree treeSort;
    for (int i = 0; i < size; i++) {
        treeSort.insertEntry(rand() % 101);
    }
    treeSort.displayTree(true);
    return 0;
}
