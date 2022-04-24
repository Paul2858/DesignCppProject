#ifndef GRAPH
#define  GRAPH
#include <iostream>
#include <vector>

typedef std::pair<int, int> Pair;
struct Edge {
  int src, dest, weight;
};

class Graph {
public:
  std::vector<std::vector<Pair>> adjList;
  Graph(std::vector<Edge> &, int);
};

void printGraph(Graph &graph, int n);
#endif