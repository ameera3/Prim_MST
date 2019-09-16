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
		vector<MinHeapNode*>& node_map,
		vector<Edge*>& edge_map) {

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
	int numVertices, numEdges; // number of vertices and edges
	ss >> temp; // extract number of vertices
        stringstream(temp) >> numVertices;
	temp = ""; // clear temp
	ss >> temp; // extract number of edges
	stringstream(temp) >> numEdges;
	temp = ""; // clear temp	
	ss.str(""); // reset string stream to be empty
	ss.clear(); // reset error flags

	// create array of numVertices MinHeapNode* pointers
	MinHeapNode** hpArray = new MinHeapNode*[numVertices];

	// fill the array with MinHeapNodes and create the node map
	for(int i = 0; i < numVertices; ++i) {
		node_map.push_back( new MinHeapNode(i+1) );
		hpArray[i] = node_map[i];
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
		MinHeapNode* sourceNode = node_map[source-1];
		MinHeapNode* destNode = node_map[dest-1];
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

	vector<MinHeapNode*> myNodeMap;
	vector<Edge*> myEdgeMap;
	MinHeapNode** myHeapArray = loadfromFile(argv[IN_IDX], myNodeMap, myEdgeMap);
	
	// no memory leaks here
	for( auto it = myNodeMap.begin(); it != myNodeMap.end(); ++it ){
		delete *it;
	}
	for( auto it = myEdgeMap.begin(); it != myEdgeMap.end(); ++it ){
		delete *it;
	}
	delete[] myHeapArray;	

}

