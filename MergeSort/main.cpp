#include <iostream>
#include "mergesort.h"
using namespace std;

int main(void) {
	int C[] = {3, 6, 91, 2, 16, 47, 34, 0, 7, 25, 19, 3, 45};
	int arrSize = sizeof(C) / sizeof(*C);	
	mergeSort(C, arrSize);
	for(int i = 0; i < arrSize; i++) 
		cout << C[i] << " ";
	cout << endl;
	return 0;
}