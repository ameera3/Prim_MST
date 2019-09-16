/* Filename: Prim.cpp
 * Description: The command line program, Prim.cpp, takes in one parameter,
 *              an input file name. The input file specified by the input
 *              file name should describe an undirected graph with integer
 *              edge costs in the following format:
 *              [number of nodes][number of edges]
 *              [one node of edge 1][other node of edge 1][weight of edge 1]
 *              .
 *              .
 *              .
 *              The program will run Prim's algorithm on the given graph
 *              and output the cost of a minimum spanning tree.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "MinHeap.hpp"
#include "MinHeapNode.hpp"
#include "Edge.hpp"

// argv index of input file
#define IN_IDX 1

// expected number of argument
#define EXPECTED_ARGS 2

using namespace std;

/* Prim's Algorithm: 
 * 1. Initialize a tree with the vertex labeled 1.
 * 2. Grow the tree by one edge: of the edges that connect the tree 
 * to vertices not yet in the tree, find the minimum-weight edge, 
 * and transfer it to the tree. 
 * 3. Repeat step 2 until all vertices are in the tree.
 */
int Prim(MinHeapNode** hpArray, int size) {

	// cost of a minimum spanning tree
	int costMST = 0;

	// Step 1: initialize a tree with the vertex labeled 1
	MinHeapNode* v1 = hpArray[0];
	v1->cost = 0;

	// create heap from array
	MinHeap* heap = new MinHeap(hpArray, size);

	/* Repeat the following steps until the heap is empty:
	 * Find and remove a vertex v from heap having minimum cost. 
	 * Add the cost of v to the cost of the MST.
	 * Pop v from the heap
	 * Loop over the edges vw connecting v to other vertices w. 
	 *  For each such edge, if w has not been popped from heap 
	 *  and vw has smaller weight than cost of w, perform the 
	 *  following steps:
		Set w's cost to the cost of edge vw
		Set w's connecting edge to point to edge vw.
	 */		
	while( !heap->empty() ) {
		MinHeapNode* current = heap->top();
		costMST += current->cost;
		current->popped = true;
		heap->pop();
		for (auto it = ((current)->incidentEdges).begin(); 
		  it != ((current)->incidentEdges).end();
		  ++it) {
		  	MinHeapNode* otherVertex = (*it)->dest;
			if ( (*it)->source != current ) {
				otherVertex = (*it)->source;
			}
			if ( !otherVertex->popped ) {
				if ( (*it)->cost < otherVertex->cost ) {
					otherVertex->connEdge = *it;
					heap->decreaseKey( 
						otherVertex->heapPos, (*it)->cost );
				}	
			}
		}	
	}

	// no memory leaks here
	delete heap;
	return costMST;	
	
}	

MinHeapNode** loadfromFile(const char* filename, 
		vector<Edge*>& edge_map,
		int* numV) {

	// used to get each line from input file
	string line;

	// used for parsing line
	stringstream ss;

	// used for parsing line
	string temp;

	// input file stream
	ifstream* in = new ifstream(filename);

	// Raise an error if file can't be read
	if( in->eof() ){
		cerr << "Failed to read " << filename << "!\n";
		delete in;
		exit(-1);
	}

	// store the total number of vertices and edges
	getline(*in, line);
	ss << line; // storing line into stringstream
	ss >> temp; // extract number of vertices
        stringstream(temp) >> *numV;
	temp = ""; // clear temp
	int numEdges; // number of edges
	ss >> temp; // extract number of edges
	stringstream(temp) >> numEdges;
	temp = ""; // clear temp	
	ss.str(""); // reset string stream to be empty
	ss.clear(); // reset error flags

	// create array of numV MinHeapNode* pointers
	MinHeapNode** hpArray = new MinHeapNode*[*numV];

	// fill the array with MinHeapNodes 
	for(int i = 0; i < *numV; ++i) {
		hpArray[i] = new MinHeapNode(i+1);
	}

	// to check if we parsed file correctly
	int edgeCount = 0;

	while(getline(*in, line)) {

		int source; // source label
		int dest; // destination label
		int weight; // edge weight

		ss << line; // storing line in stringstream
		ss >> temp; // extract source label
		stringstream(temp) >> source; // store source label
		temp = ""; // clear temp
		ss >> temp; // extract dest label
		stringstream(temp) >> dest; // store dest label
	        temp = ""; // clear temp
		ss >> temp; // extract edge weight
		stringstream(temp) >> weight;	
		MinHeapNode* sourceNode = hpArray[source-1];
		MinHeapNode* destNode = hpArray[dest-1];
		edge_map.push_back( 
			new Edge(sourceNode, destNode, weight) );
		(sourceNode->incidentEdges).push_back(
			edge_map[edgeCount]);
		(destNode->incidentEdges).push_back(
			edge_map[edgeCount]);
		
		// reset the string stream to be empty and
		// reset error flags
		ss.str("");
		ss.clear();

		// increment the edge count
		++edgeCount;

	}

	// check that you read in the correct number of edges
	if( edgeCount != numEdges ){
		cerr << "Incorrect Parse!" << endl;
		delete in;
		exit(-1);
	}

	// no memory leaks here
	delete in;

	// return heap array
	return hpArray;
}

		
int main(int argc, char** argv) {

	// Check for arguments
	if( argc != EXPECTED_ARGS ){
		cout << "This program requires 2 arguments" << endl;
		return -1;
	}

	// used to delete edges
	vector<Edge*> myEdgeMap;

	// number of vertices
	int numVertices;

	// read from the input file and create the heap
	MinHeapNode** myHeapArray = loadfromFile(argv[IN_IDX], myEdgeMap, &numVertices);

	// run Prim's algorithm
	int myMSTcost = Prim(myHeapArray, numVertices);

	// output the cost of an MST
	cout << "cost: " << myMSTcost << endl;

	// no memory leaks here
	for( auto it = myEdgeMap.begin(); it != myEdgeMap.end(); ++it ){
		delete *it;
	}
	for( int i = 0; i < numVertices; ++i ){
		delete myHeapArray[i];
	}
	delete[] myHeapArray;	

}

