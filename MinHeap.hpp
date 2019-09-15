/*
 * Filename: MinHeap.hpp
 * Description: Implements a min heap for use in Prim's MST Algorithm
 */

#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include "MinHeapNode.hpp"

/* Class Name: MinHeap
 * Instance Variables: heapArray (pointer to array representation of heap)
 *                     heapSize (number of nodes in the heap)
 * Description: Implements a min heap for use in Prim's MST Algorithm.
 * Public Methods: Constructor, minHeapify, left, right, parent, top, pop, 
                   exchange, destructor.
 */
class MinHeap
{
    // pointer to array representation of heap		
    MinHeapNode** heapArray; 

    // number of nodes in heap 
    int heapSize;       
    
    public:

	// Constructor  
	MinHeap(MinHeapNode* a[], int size);

	// Heapify a subtree with root at given index j 
	void minHeapify(int j);

	// Analogue of priority queue empty
	bool empty();

	// Get index of left child of node at index j 
	int left(int j);

	// Get index of right child of node at index j 
	int right(int j);

	// Get parent of node at index j
	int parent(int j);

	// Analogue of priority queue top 
	MinHeapNode* top();

	// Analogue of priority queue pop
	MinHeapNode* pop(); 

	// Decrease Key and fix any heap violations that occur
	void decreaseKey(int i, int newVal);

	// swaps two min heap nodes
	void exchange(MinHeapNode** a, MinHeapNode** b, int aPos, int bPos);

	// destructor
	~MinHeap();
};

#endif // MIN_HEAP_H
