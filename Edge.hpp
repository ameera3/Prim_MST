/*
 * Filename: Edge.hpp
 * Description: Implements an edge class for a graph on
 *              which we will apply Prim's MST Algorithm.
 */

#ifndef EDGE_HPP
#define EDGE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Forward declaration of MinHeapNode class
 */
class MinHeapNode;

/* 
 * Class name: Edge
 * Instance Variables: source (MinHeapNode pointer to source)
 *                     dest (MinHeapNode pointer to dest)
 *                     cost (integer valued cost)
 *                     Although the edges are unordered, we
 *                     will store each edge with the vertex
 *                     with the lower valued label as the 
 *                     source and the higher valued label as
 *                     the destination.             
 * Description: Implements an edge class for a graph on which
 *              we will apply Prim's MST algorithm.                  
 * Public Methods: constructor
 * Private Methods: None                    
*/

class Edge {

    public:

        // Source
        MinHeapNode* source;

        // Destination
        MinHeapNode* dest;

	// Cost
	int cost;

        // Constructor 
        Edge(MinHeapNode* low, MinHeapNode* high, int weight) :
            source(low), dest(high), cost(weight) {} 

};

#endif // EDGE_HPP
