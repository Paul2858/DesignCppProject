#ifndef PATHFINDER
#define PATHFINDER
#include "Graph.h"

class PathFinder {
public:
	// PathFinder();
	static std::vector<int> AStar(Graph &graph, int start, int end);
	/*
	GeneralMapObject createPathFinder(){
		// takes in as input the "map", start, finish and returns relevant object
	}	

	GeneralPath findShortestPath(){
		// returns shortest path of a GeneralMapObject given start and end
		// Runs Dijkstra if GeneralMapObject is graph
		// Runs backtracking algorithm if maze/matrix
	}
	*/
	// std::vector<Edge>
};
#endif