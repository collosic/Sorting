bool ascending(int a, int b);
bool descending(int a, int b);
int selectPivot(int *arr, int size);
void sortLessThanFour(int *array, int size, bool (*compare) (int, int));
void combineSort(int *arr, int *f_half, int size_f, int *s_half, int size_s);
int* sort(int* a, int size, bool (*compare) (int, int));
void quicksort(int *arr, int size, bool order);