#include <iostream>
#include "insertsort.h"
using namespace std;

int main(void) {
    int array[] = {3, 24, -9, 10, 35, 24, 56, 980, 1};
    int sizeOfArray = sizeof(array) / sizeof(*array);
    insertSort(array, sizeOfArray);
    
    for(int i = 0; i < sizeOfArray; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    return 0;
}    
    
   
