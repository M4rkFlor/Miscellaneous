#ifndef HEAP_H
#define HEAP_H
class MaxHeap
{
    int *arr;		// pointer to array of elements in heap
    int capacity;	// maximum possible size of min heap
    int size;		// Current number of elements in min heap
	
	int parent(int i); //parent indexing
    int left(int i); //left node indexing
    int right(int i);//right  node indexing
    bool isLeaf(int i); //checks if leaf
    void siftup(int i); //siftup arrocding to max heap
    void siftdown(int i); //sift down arcding to maxheap
    void swap(int *x, int *y); //swaps 2 numbers
public:
    class Overflow{};//Error handling 
    class Underflow{};//Error handling 
    MaxHeap(int capacity);//ocmstutor
	int getSize();//gets size
	int getMax();//get max element
	void insert(int k);//insert element in maxheap
    int extractMax(); //gets max and removes it
	int removeAt(int i);//removes the ith eleemnt
    void heapify(int *array, int len);//turns an array to heap
};
#endif