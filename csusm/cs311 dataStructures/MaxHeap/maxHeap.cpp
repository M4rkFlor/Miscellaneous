#include "maxHeap.h"
//Marco Flores
//Max Heap
int MaxHeap::parent(int i) { return (i-1)/2; }//Array Indexing for heap parent node
int MaxHeap::left(int i) { return (2*i + 1); }//Array Indexing for heap left leaf node
int MaxHeap::right(int i) { return (2*i + 2); }//Array Indexing for heap right leaf node
bool MaxHeap::isLeaf(int i) {return (i < size/2) ? false : true;}//Array Indexing for heap and checks if the indeex is leaf
void MaxHeap::swap(int *x, int *y) {int temp = *x;*x = *y;*y = temp;} //swaps 2 numbers
void MaxHeap::siftup(int i){ 
    while(i > 0 && arr[parent(i)] < arr[i]){  // shift up while parent node is smaller than new node
        swap(&arr[i], &arr[parent(i)]);
        i = parent(i); //recalculate parent
    }
}
void MaxHeap::siftdown(int i) {//BRACKETS MAY BE MISSALIGNED AND MISSING CODE
    while(!isLeaf(i)) {
        int l = left(i);
        int r = right(i);//aquire left and right leaf nodes
        int smaller = arr[l];//store left leaf
        if(r < size) 
            smaller = (arr[l] > arr[r]) ? l : r;//store bigest leaf value although the varible name is smaller
        if(arr[i] >= arr[smaller])
            break;
        swap(&arr[i], &arr[smaller]);
        i = smaller;// recalculate index
    }
}

MaxHeap::MaxHeap(int cap) //constructor to initialiuze values
{
    capacity = cap;
    size=0; //these values dont matter to much if heapify is used
    arr = new int[capacity]; 
}
int MaxHeap::getSize(){ return size; } //returns the number of elements in heap
void MaxHeap::insert(int k) {
    if (size >= capacity)
        throw Overflow(); //detect Overflow
    int i = size;
    arr[i] = k;//insert at end
    siftup(i);size++;
}
int MaxHeap::removeAt(int i) { 
    if(i <0|| size <= i) 
        throw Underflow();//Underflow detection
    if(size ==1) 
        return arr[--size];//only 1 element
    int result = arr[i];
    arr[i] = arr[--size];//swap with last node
    if(arr[i] < result) //if greater sift down
        siftdown(i); 
    else 
        siftup(i);//otehrwise sift up
    return result;//return the removed value
}
int MaxHeap::extractMax() { //get the max and removes it from heap
    if(size <=0) 
        throw Underflow();
    if(size ==1) 
        return arr[--size]; //if only one element
    int result = arr[0]; 
    arr[0] = arr[--size]; 
    siftdown(0); //swap with last element and sift down
    return result;//return max
}
int MaxHeap::getMax() { return arr[0];}//gets the max value without altering heap
void MaxHeap::heapify(int *array, int len){ //heapifies array
    arr = array; 
    capacity = size = len;
    int half = size/2 - 1;// the index of the last internal node
    for(int i = half; i >=0; i--) 
        siftdown(i);
    }
