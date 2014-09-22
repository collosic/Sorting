/* Insertsort that takes in a pointer to the first element 
 * in an unsorted array and sorts the array using the 
 * insertsort algorithm
 */
    
void determinePlacement(int *arr, int index) {
    while(index > 0) {
        if(arr[index] < arr[index - 1]) {
            arr[index - 1] = arr[index - 1] xor arr[index];
            arr[index] = arr[index - 1] xor arr[index];
            arr[index - 1] = arr[index - 1] xor arr[index];
            index--; 
        } else
            break;
    }
}

void insertSort(int *unsorted, int size) {
    for(int i = 1; i < size; i++) 
        determinePlacement(unsorted, i); 
}


