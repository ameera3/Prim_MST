/* Filename: Prim.cpp
 * Description:
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

MinHeapNode** loadfromFile(const char* filename, 
		vector<MinHeapNode*>& node_map
		vector<Edge*>& edge_map) {

	// used to get each line from input file
	string line;

	// input file stream
	ifstream* in = new ifstream(filename);

	// Raise an error if file can't be read
	if( in->eof() ){
		cerr << Failed to read " << filename << "!\n";
		delete in;
		exit(-1);
	}

	// store the total number of vertices and edges
	getline(*in, line);
	stringstream ss; // used for parsing line
	ss << line; // storing line into stringstream
	string temp; // used for parsing line
	int numVertices; // number of vertices
	int numEdges; // number of edges
	ss >> temp; // extracting number of vertices
	stringstream(temp) >> numVertices // store in numVertices
	temp = ""; // clear temp
        ss >> temp; // extract number of edges
	stringstream(temp) >> numEdges; // store in numEdges
	ss.str(""); // reset string stream to be empty

	// create array of numVertices MinHeapNode* pointers
	MinHeapNode** hpArray = new MinHeapNode[numVertices];

	// fill the array with MinHeapNodes and create the node map
	for(int i = 0; i < numVertices; ++i) {
		hpArray[i] = node_map[i] = new MinHeapNode(i + 1);
	}

	// to check if we parsed file correctly
	int edgeCount = 0;

	while(getline(*in, line)) {

		int source; // source node
		int dest; // destination node
		int weight; // edge weight

		ss >> temp; // extract source

		// check source is int 
		if( stringstream(temp) >> source ){

			// clear temp
			temp = "";

			// extract dest
			ss >> temp;

			// check dest is int
			if( stringstream(temp) >> dest ){

				// clear temp
				temp = "";

				// extract weight, create edge, add edge to
				// incidentEdges of sourceNode and destNode,
				// add edge to edge_map
				if( stringstream(temp) >> weight ){
					MinHeapNode* sourceNode = node_map[source];
					MinHeapNode* destNode = node_map[dest];
					Edge* edge = 
					new Edge(sourceNode, destNode, weight);
					edge_map[edgeCount] = edge;
					(sourceNode->incidentEdges).push_back(edge);
					(destNode->incidentEdges).push_back(edge);
				}
			}	
		}

		// reset the string stream to be empty
		ss.str("");

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

	vector<MinHeapNode*> myNodeMap;
	vector<Edge*> myEdgeMap;
	MinHeap** myHeapArray = loadfromFile(argv[IN_IDX], myNodeMap, myEdgeMap);
	
	

	return 0;

}

