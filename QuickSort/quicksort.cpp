/* My implementation of the quicksort algorithm.  This program will allow for
 * ascending and descending ordering.  
 */
#include <stdlib.h>
#include <time.h>

// Used to determine the ordering of the sorting
bool ascending(int a, int b) {
    return b < a;
}

bool descending(int a, int b) {
    return b > a;
}

// Swaps two variables from the caller.  Uses references.
void swap(int &a, int &b) {
    a = a xor b;
    b = a xor b;
    a = a xor b;
}

// Used to generate unique random indexes, so that no duplicates appear.
int noDups(int *arr, int size, int *p_arr, int p_size) {
    bool go_again;
    int random;
    do {
        go_again = false;
        random = rand() % size;
        for(int i = 0; i < p_size; i++) {
            if(p_arr[i] == random) {
                go_again = true;
            }
        }
    } while(go_again);
    return random;
}

// Will sort an array if it has less than 4 integers.  If 0 or 1 integers it does nothing.
// If 2 or 3 integers then it will decide what order to arrange the array.
void sortLessThanFour(int *array, int size, bool (*compare) (int, int)) {
    if(size == 2) {
        if(compare(array[0], array[1]))
            swap(array[0], array[1]);
    }
    if (size == 3) {
        if(compare(array[0], array[1]))
            swap(array[0], array[1]);
        if(compare(array[1], array[2]))
            swap(array[1], array[2]);
        if(compare(array[0], array[1]))
            swap(array[0], array[1]);
    }
}

// This will randomly select 3 numbers from the array and returns the index 
// of the median.
int selectPivot(int *arr, int size) {
    int possible_pivot_index[3];
    int possible_pivots[3];
    int pivot = -1;
    for(int i = 0; i < 3; i++) {
        possible_pivot_index[i] = noDups(arr, size, possible_pivot_index, i);
        possible_pivots[i] = arr[possible_pivot_index[i]];
    }

    sortLessThanFour(possible_pivots, 3, ascending);
    for (int i = 0; i < 3; i++) {
        if(possible_pivots[1] == arr[possible_pivot_index[i]]) {
            pivot = possible_pivot_index[i];
            break;
        }
    }
    return pivot;
}

// This will combine the first and second halves of these sorted arrays into
// the original array from which they were generated.
void combineSort(int *arr, int *f_half, int size_f, int *s_half, int size_s) {
    int total_size = size_f + size_s;
    int i = 0, j = 0, k = 0;
    while (k < total_size) {
        if(i < size_f)
            arr[k++] = f_half[i++];
        else
            arr[k++] = s_half[j++];
    }
}
        
// A recursive function that uses the quicksorting algorithm.
int* sort(int* a, int size, bool (*compare) (int, int)) {
    int pivot_index;
    if(size > 3)
        pivot_index = selectPivot(a, size);
    else {
        sortLessThanFour(a, size, compare);
        return a;
    }
    
    int *first_half = new int [size];
    int *second_half = new int [size];
    int j = 0, k = 0;
    for(int i = 0; i < size; i++) {
        if(i == pivot_index)
            continue;
        else {
            if(compare(a[pivot_index], a[i]))
                first_half[j++] = a[i];
            else
                second_half[k++] = a[i];
        }
    }
    // Place the pivot at the end of the first half
    first_half[j++] = a[pivot_index];

    // Merger the two sorted halves into the original array
    combineSort(a, sort(first_half, j, compare), j, sort(second_half, k, compare), k);

    // delete the arrays
    delete[] first_half;
    delete[] second_half;
    return a;   
}


/* This function will take a pointer to the first elemnt in an aay, the size of the aay, and
 * a boolean value representing ascending (true) or descending (false) order.
 */
void quicksort(int *arr, int size, bool order) {
    srand (time(NULL));
    order ? sort(arr, size, ascending) : sort(arr, size, descending);
}






