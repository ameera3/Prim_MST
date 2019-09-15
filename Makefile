# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall 
LDFLAGS=-g

all: Prim 

Prim: MinHeap.o

MinHeap.o: MinHeap.hpp MinHeapNode.hpp Edge.hpp 

clean:
	rm -f Prim *.o core* *~
