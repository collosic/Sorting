#include <iostream>
#include "bubblesort.h"
using namespace std;

int main(void) {
    int array[] = {24, 24, -9, 10, 35, 56, 980};
    int sizeOfArray = sizeof(array) / sizeof(*array);
    bubbleSort(array, sizeOfArray);
    
    for(int i = 0; i < sizeOfArray; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    return 0;
}    
    
   
