/* This will sort an array in ascending order using the Bubblesorting
 * algorigthm.  It will have a worst case O(n^2). */

bool bubbleUp(int *arr, int unsortdedLength);
void swapElements(int *element, int index);


void bubbleSort(int *unsorted, int size) {
    bool isSorted = false;
    for(int i = size; i > 1; i--) {
        if(isSorted) 
            break;
        else
            isSorted = bubbleUp(unsorted, i);
    }
}

bool bubbleUp(int *arr, int unsortedLength) {
    bool wasSwapped = false;
    for(int j = 1; j < unsortedLength; j++) {
        if(arr[j - 1] >= arr[j]) {
            if(arr[j - 1] != arr[j]) {
                swapElements(arr, j);
                wasSwapped = true;
            }
        } else  
            return !wasSwapped;
    }
    return !wasSwapped;
}

void swapElements(int *element, int index) {
    element[index] = element[index] xor element[index - 1];
    element[index - 1] = element[index] xor element[index - 1];
    element[index] = element[index] xor element[index - 1];
}

