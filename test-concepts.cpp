#include "Graph.h"
#include <string>
#include <iostream>
// #include "PathFinder.h"

/*
Concept for graph input: {adjacency matrix of: node type, node type, weight type} (weight type comparable)
Concept for matrix input: {something indexable[][], free type}
*/
/*
  GRAPH INPUT (list):

  {0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {5, 4, 1}, {4, 5, 3}
  {0, 1},    {1, 2},    {2, 0}

  {Tile1.ID, Tile2.ID, Score}, {}{}
  map of node-type / id (or address) to int index
  +
  adjacency list
  [
    0: [(1, 2), (2, 10)],
    1: [(0, 4)],
    2: [(1, 3), (0, 5)],
    ...
  ]
*/

/*
  GRAPH INPUT (adjacency matrix)
  {
    NodeID: {NodeID NodeID NodeID},
    NodeID: {NodeID NodeID NodeID},
    NodeID: {NodeID NodeID NodeID}
  }
*/

/*
  MATRIX INPUT:
  {
    {0, 0, 0, 0, 1, 1, 0}
    {0, 0, 0, 0, 1, 1, 0}
    {0, 1, 0, 0, 1, 1, 0}
    {0, 1, 1, 0, 1, 1, 0}
    {0, 0, 1, 0, 0, 0, 0}
  }
  {
    0: {NodeId, NodeId, ObstacleType, PrizeType, NodeId},
    1: {NodeId, NodeId, ObstacleType, ObstacleType, NodeId},
    ...
  }
*/
struct Edge {
  std::string src, dest;
  int weight;
};
int main() {
  std::vector<Edge> edges = {
    // (x, y, w) —> edge from `x` to `y` having weight `w`
    {"heyo", "bro", 6}
    //, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {5, 4, 1}, {4, 5, 3}
  };
  Graph<Edge, std::string, int> graph(edges);

  std::cout << "(" << graph.adjList["heyo"][0].first << ", " << graph.adjList["heyo"][0].second << ")" << '\n';

  PathFinder pf(graph);
  // pf.AStart(3, 1);

  // std::vector<int> sp = PathFinder::AStar(graph, 3, 1);
  // std::cout << "Found path: [ ";
  // for (int i : sp)
  //   std::cout << i << ' ';
  // std::cout << "]\n";
}