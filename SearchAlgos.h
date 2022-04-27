#ifndef SEARCHALGOS
#define SEARCHALGOS
#include "Graph.h"

class SearchAlgos
{
public:
    static std::vector<int> BreadthFirstSearch(Graph &graph, int start, int target);
    static std::vector<int> DepthFirstSearch(Graph &graph, int start, int target);
};
#endif