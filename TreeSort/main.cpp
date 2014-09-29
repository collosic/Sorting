// Example main.cpp on how to use treesort.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "treesort.h"


int main() {
    int size = 30;
    srand(time(NULL));
    BinarySearchTree treeSort;
    for (int i = 0; i < size; i++) {
        int var = rand() % 201;
        treeSort.insertEntry(var);
    }
    treeSort.displayTree(true);
    return 0;
}
