# Prim_MST

## Usage
To compile, type "make". To run the program, type "./Prim edges.txt".

## Introduction
The command line program, Prim.cpp, takes in one parameter,
an input file name. The input file specified by the input
file name should describe an undirected graph with integer
edge costs in the following format:

[number of nodes][number of edges]

[one node of edge 1][other node of edge 1][weight of edge 1]
 
                .
                .
                .
 The program will run Prim's algorithm on the given graph
 and output the cost of a minimum spanning tree.
 
 To implement Prim's algorithm efficiently in O(m log n) time, 
 we wrote our own priority queue (minHeap) data structure in C++ 
 that includes a decrease key functionality.
