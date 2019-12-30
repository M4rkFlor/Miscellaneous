//Marco Flores
#include <iostream>
 
using namespace std;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
int partition (int arr[], int low, int high)
{
    //////////////////////////////////////
    int p = arr[high];
    int pIndex=high;
        while (low < high) {
            while (arr[low] <= p && low<high) low++;
            while (arr[high] >= p && low<high) high--;
            if (low < high) {
                    swap(&arr[low],&arr[high]);
            }
        }
        //swap pivot
        swap(&arr[low],&arr[pIndex]);
        return low;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
 
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, n-1);
    cout << "Sorted array: " << endl;
    printArray(arr, n);
    return 0;
}