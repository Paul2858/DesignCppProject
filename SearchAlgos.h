#ifndef SEARCHALGOS
#define SEARCHALGOS
#include "Graph.h"

class SearchAlgos
{
public:
    static void BreadthFirstSearch(Graph &graph, int start);
    static void DepthFirstSearch(Graph &graph, int start);
};
#endif