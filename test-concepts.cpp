// #include "Graph.h"
#include "APathy.h"
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
// (x, y, w) —> edge from `x` to `y` having weight `w`
struct Edge {
  std::string src, dest;
  int weight;
};
int main() {
  std::vector<Edge> edges = {
    {"0", "1", 6},
    {"1", "2", 7},
    {"2", "0", 5},
    {"2", "1", 4},
    {"3", "2", 10},
    {"5", "4", 1},
    {"4", "5", 3}
  };
  
  APathy<Edge, std::string, int> finder(edges);
  std::vector<std::string> sp = finder.AStar("3", "1");

  /* PRINT THE SHORTEST PATH IT FOUND */
  std::cout << "Found path: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "]\n";
}