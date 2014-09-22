/* 
	Building a merge sort algorithm based on 
	the course called 'Algorithms: Design and Analysis'
	from Coursera.
*/

int* mergeSort(int *unsortedArray, int length);
int* merge(int *A, int sizeA, int *B, int sizeB);
void checkForSwap(int *array);
void copyNewSortedArray(int *A, int *temp, int length);

int* mergeSort(int *arr, int length) {
	if (length < 3) {
		if (length == 2)
			checkForSwap(arr);
		return arr;
	} else {
		int split = length / 2;
		int sizeOfA = split;
		int sizeOfB = (length % 2 == 0) ? split : split + 1;
		int *A = arr;
		int *B = (A + sizeOfA);
		return merge(mergeSort(A, sizeOfA), sizeOfA, mergeSort(B, sizeOfB), sizeOfB);
	}
}

int* merge(int *A, int sizeA, int *B, int sizeB) {
	int n = sizeA + sizeB;
	int temp[n];
	int i = 0;
	int j = 0;
	for(int k = 0; k < n; k++) {
		if(i == sizeA)
			temp[k] = B[j++];
		else if (j == sizeB)
			temp[k] = A[i++];
		else if(A[i] < B[j] && i < sizeA) 
			temp[k] = A[i++];
		else if (B[j] < A[i] && j < sizeB)
			temp[k] = B[j++];
		else {
			// this means A[i] == B[j]
			temp[k] = A[i++];
		}
	}
	copyNewSortedArray(A, temp, n);
	return A;
}

void checkForSwap(int *array) {
	if(array[0] > array[1]) {
		array[0] = array[0] xor array[1];
		array[1] = array[0] xor array[1];
		array[0] = array[0] xor array[1];
	}
}

void copyNewSortedArray(int *A, int *temp, int length) {
	for(int i = 0; i < length; i++)
		A[i] = temp[i];
}