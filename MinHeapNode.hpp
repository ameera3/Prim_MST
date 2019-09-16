/* Filename: MinHeapNode.hpp
 * Description: Implements a MinHeap node for use in Prim's Algorithm
 */

#ifndef MIN_HEAP_NODE_HPP
#define MIN_HEAP_NODE_HPP

#include<limits>
#include<vector>

using namespace std;

/* Forward Declaration of Edge Class */
class Edge;

/* Class Name: MinHeapNode
 * Instance Variables: label (integer vertex label)
 *                     cost (integer cost of cheapest edge connecting vertex 
 *		             to MST -- initially each vertex has cost INT_MAX)
 *		       heapPos (position in heap)
 *		       popped (bool indicating whether vertex has been popped from
 *		               heap or not -- initially set to false)	     
 *		       connEdge (cheapest edge connecting vertex to MST)
 *		       incidentEdges (vector of edges incident with vertex)
 * Public Methods: Constructor
 */

class MinHeapNode
{
	public:

		/* vertex label */
		int label;

		/* cost of cheapest edge connecting vertex to MST */    
		int cost;

		/* position in heap */
		int heapPos;

		/* whether it has been popped from heap or not */
		bool popped;

		/* cheapest edge connecting vertex to MST */
		Edge* connEdge;

		/* all edges incident with vertex */
		vector<Edge*> incidentEdges;

		/* Constructor */
		MinHeapNode(int name) :
			label(name), cost(std::numeric_limits<int>::max()),
       			heapPos(name-1), popped(false)	{}

};

#endif // MIN_HEAP_NODE_HPP



