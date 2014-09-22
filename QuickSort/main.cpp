#include <iostream>
#include "quicksort.h"
using namespace std;

int main(void) {
	int C[] = {123, 34, 0, 3, 24, 26, 0, -3, 5, 32, 67, 14};
	int arrSize = sizeof(C) / sizeof(*C);
	bool isAsc = true;
	bool isDsc = !isAsc;

	quicksort(C, arrSize, isDsc);
	for(int i = 0; i < arrSize; i++) 
		cout << C[i] << " ";

	cout << endl;
	return 0;
}
