/*
 * Filename: MinHeap.cpp
 * Description: Implements the methods of MinHeap class
 */

#include "MinHeap.hpp"
#include "MinHeapNode.hpp"

// Constructor: Builds a heap from a given array a[] 
// of given size 
MinHeap::MinHeap(MinHeapNode* a[], int size)
{
	heapSize = size;
	heapArray = a; // store address of array
        
	// fix heap violations for the first half
	// of the heap.	
	int i = (heapSize - 1) / 2;
	while (i >= 0)
	{
		minHeapify(i);
		i--;
	}
}

// A recursive method to heapify (aka bubble down) 
// a subtree with root at given index. This method 
// assumes that the subtrees are already heapified 
void MinHeap::minHeapify(int j)
{
	// check if there are any heap violations
	// between j and its childen. If there are,
	// then smallest != j.
	int l = left(j); // left child of j
	int r = right(j); // right child of j
	int smallest = j; // smallest key value among j and children
	if (l < heapSize && heapArray[l]->cost < heapArray[j]->cost)
		smallest = l;
	if (r < heapSize && heapArray[r]->cost < heapArray[smallest]->cost)
		smallest = r;

	// if j has a heap violation with one or more of its children,
	// swap j with its child of smallest key value and then recursively
	// bubble down on smallest.
	if (smallest != j)
	{
		exchange(&heapArray[j], &heapArray[smallest], j, smallest);
		minHeapify(smallest);
	}
}

// Analogue of priority queue empty
bool MinHeap::empty()
{
	if( heapSize == 0 ){
		return true;
	}
	return false;
}

// returns position of left child in array
// representation of heap
int MinHeap::left(int j) 
{ 
	return (2 * j + 1); 
}

// returns position of right child in array 
// representation of heap
int MinHeap::right(int j) 
{ 
	return (2 * j + 2); 
}

// returns position of parent child in array
// representation of heap
int MinHeap::parent(int j)
{
	return (j-1)/2;
}	

// Analogue of priority queue top
MinHeapNode* MinHeap::top() 
{ 
	return heapArray[0]; 
}

// Decrease key and fix any heap violations that occur
void MinHeap::decreaseKey(int i, int newVal)
{
	// decrease i's key to newVal
	heapArray[i]->cost = newVal;

	// fix any heap violations that occur
	while( i > 0 && heapArray[parent(i)]->cost > heapArray[i]->cost ){
		exchange(&heapArray[i], &heapArray[parent(i)], i, parent(i));
		i = parent(i);
	}
}		

// exchanges two min heap nodes
void MinHeap::exchange(MinHeapNode** a, MinHeapNode** b, int aPos, int bPos) 
{
	(*a)->heapPos = bPos;
	(*b)->heapPos = aPos;
	MinHeapNode* temp = *a;
	*a = *b;
	*b = temp;
}

// Analogue of priority queue pop 
MinHeapNode* MinHeap::pop()
{
	if (heapSize <= 0) {
		return nullptr;
	}
        if (heapSize == 1)
        {
                heapSize--;
                return heapArray[0];
        }

        /* Store the node with minimum key value
	 * Exchange the root with the last leaf
	 * Decrement the heapSize
	 * Bubble down at the root
	 */ 
        MinHeapNode* root = heapArray[0];
        exchange(&heapArray[0], &heapArray[heapSize-1], 0, heapSize - 1);
        heapSize--;
        minHeapify(0);

	/* return the node with minimum value */
        return root;
}

// destructor
MinHeap::~MinHeap() {}
