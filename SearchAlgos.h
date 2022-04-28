#ifndef SEARCHALGOS
#define SEARCHALGOS
#include "Graph.h"

class SearchAlgos
{
public:
    static std::vector<ID> BreadthFirstSearch(ID start, ID target);
    static std::vector<ID> DepthFirstSearch(ID start, ID target);
};
#endif